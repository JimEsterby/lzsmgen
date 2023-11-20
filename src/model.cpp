#include "model.h"
extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<array>

///// Test Area
#ifdef DEBUG
// kludge to enable a sort of mocking
#undef luaL_loadfile
#define luaL_loadfile(L, fn)  mock_luaL_loadfilex(L, fn, __null)
static bool script_load_fail = false;
void simulate_script_load_failure(bool value)
{
    script_load_fail = value;
}
extern "C" int mock_luaL_loadfilex(lua_State *L, const char *filename, const char *access)
{
    int result = 1;
    if (script_load_fail == false)
    {
        result = luaL_loadfilex(L, filename, access);
    }

    return result;
}
#endif
///// End of Test Area

Model* theModel;

const char* Model::main_script = "lzsmgen.lua";
const char* Model::during_suffix = "do";
const char* Model::entry_suffix = "entry";
const char* Model::t_action_suffix = "action";

Model::Model()
{
    m_diagram = new Diagram;
    m_diagram_file = new std::string;
    m_module_base_name = new std::string;

    // Attempt to start the interpreter
    failed_interpreter = initialize_interpreter(&m_Lua) ? false : true;
}

Model::Model(const char* file_name)
{
    std::size_t extension;

    m_diagram = new Diagram;
    m_diagram_file = new std::string(file_name);
    m_module_base_name = new std::string(file_name);

    extension = m_module_base_name->rfind('.');
    if (extension != std::string::npos)  // No extension
    {
        m_module_base_name->erase(extension);
    }

    // Attempt to start the interpreter
    failed_interpreter = initialize_interpreter(&m_Lua) ? false : true;
}

Model::~Model()
{
    delete m_diagram;
    delete m_diagram_file;
    delete m_module_base_name;
    lua_close(m_Lua);
}

Diagram* Model::diagram() const
{
    return m_diagram;
}

Diagram* Model::new_diagram()
{
    delete m_diagram;
    m_diagram = new Diagram;
    return m_diagram;
}

bool Model::file_loaded() const
{
    return !(m_diagram_file->empty());
}

const char* Model::file_name() const
{
    const char* result = NULL;

    if (file_loaded())
    {
        result = m_diagram_file->c_str();
    }

    return result;
}

void Model::file_name(const char* name)
{
    m_diagram_file->assign(name);
    set_module_base_name();
}

const char* Model::module_name() const
{
    return m_module_base_name->c_str();
}

bool Model::open_file(const char* name)
{
    int nr_states;
    int nr_transitions;
    bool result = false;

    lua_getglobal(m_Lua, "read_diagram");
    lua_pushstring(m_Lua, name);
    if (LUA_OK == lua_pcall(m_Lua, 1, 1, 0))
    {
        result = lua_toboolean(m_Lua, 1);
        lua_pop(m_Lua, 1);

        lua_getglobal(m_Lua, "nr_states");
        lua_call(m_Lua, 0, 1);
        nr_states = lua_tointeger(m_Lua, 1);
        lua_pop(m_Lua, 1);

        lua_getglobal(m_Lua, "nr_transitions");
        lua_call(m_Lua, 0, 1);
        nr_transitions = lua_tointeger(m_Lua, 1);
        lua_pop(m_Lua, 1);

        // Load states
        for (int idx = 1; idx <= nr_states; idx++)
        {
            CState* cs;
            const char* name;
            const char* entry;
            const char* during;
            bool isDefault;
            int x1, y1, x2, y2;

            lua_getglobal(m_Lua, "get_state");
            lua_pushinteger(m_Lua, idx);
            lua_call(m_Lua, 1, 8);
            name = lua_tostring(m_Lua, 1);
            entry = lua_tostring(m_Lua, 2);
            during = lua_tostring(m_Lua, 3);
            isDefault = lua_toboolean(m_Lua, 4);
            x1 = lua_tointeger(m_Lua, 5);
            y1 = lua_tointeger(m_Lua, 6);
            x2 = lua_tointeger(m_Lua, 7);
            y2 = lua_tointeger(m_Lua, 8);

            cs = new CState(name, x1, y1, x2, y2, isDefault);
            cs->entry_action(entry);
            cs->during_action(during);
        
            lua_pop(m_Lua, 8);

            m_diagram->add_state(cs);
        }

        // Load transitions
        for (int idx = 1; idx <= nr_transitions; idx++)
        {
            CTransition* ct;
            const char* name;
            const char* condition;
            const char* action;
            int priority;
            int x1, y1, x2, y2;

            lua_getglobal(m_Lua, "get_transition");
            lua_pushinteger(m_Lua, idx);
            lua_call(m_Lua, 1, 8);
            name = lua_tostring(m_Lua, 1);
            condition = lua_tostring(m_Lua, 2);
            action = lua_tostring(m_Lua, 3);
            priority = lua_tointeger(m_Lua, 4);
            x1 = lua_tointeger(m_Lua, 5);
            y1 = lua_tointeger(m_Lua, 6);
            x2 = lua_tointeger(m_Lua, 7);
            y2 = lua_tointeger(m_Lua, 8);

            ct = new CTransition(condition, name, x1, y1, x2, y2, priority);
            ct->action(action);
        
            lua_pop(m_Lua, 8);

            m_diagram->add_transition(ct);
        }

        if (!(nr_states == 0 && nr_transitions == 0))
        {
            // Get the diagram metadata if any
            lua_getglobal(m_Lua, "get_dependencies");
            lua_call(m_Lua, 0, 1);
            m_diagram->dependencies(lua_tostring(m_Lua, 1));
            lua_pop(m_Lua, 1);

            lua_getglobal(m_Lua, "get_internals");
            lua_call(m_Lua, 0, 1);
            m_diagram->internals(lua_tostring(m_Lua, 1));
            lua_pop(m_Lua, 1);

            m_diagram_file->assign(name);
            set_module_base_name();
            result = true;
        }
    }

    reset_script();   

    return result;
}

bool Model::save_file()
{
    bool result = false;
    std::list<CState*> cs;
    std::list<CTransition*> ct;

    cs = m_diagram->state_list();
    ct = m_diagram->transition_list();

    for (auto iter = cs.begin(); iter != cs.end(); iter++)
    {
        lua_getglobal(m_Lua, "create_state");
        pushstring((*iter)->name());
        pushstring((*iter)->entry_action());
        pushstring((*iter)->during_action());
        lua_pushboolean(m_Lua, (*iter)->get_default());
        pushlocation((*iter)->position());
        lua_call(m_Lua, 5, 0);
    }

    for (auto iter = ct.begin(); iter != ct.end(); iter++)
    {
        lua_getglobal(m_Lua, "create_transition");
        pushstring((*iter)->name());
        pushstring((*iter)->condition());
        pushstring((*iter)->action());
        lua_pushinteger(m_Lua, (*iter)->priority());
        pushlocation((*iter)->position());
        lua_call(m_Lua, 5, 0);
    }

    lua_getglobal(m_Lua, "write_diagram");
    lua_pushstring(m_Lua, m_diagram_file->c_str());
    lua_pushstring(m_Lua, m_diagram->dependencies());
    lua_pushstring(m_Lua, m_diagram->internals());
    if (LUA_OK == lua_pcall(m_Lua, 3, 1, 0))
    {
        result = lua_toboolean(m_Lua, 1);
    }
    lua_pop(m_Lua, 1);

    reset_script();

    return result;
}

// Check if the file exists. Normally used to prevent overwriting a file if the
// user does not explicitly want to overwrite the file.
bool Model::file_exists(const char* name) const
{
    bool result;

    if (failed_interpreter)
    {
        result = false;
    }

    else
    {
        lua_getglobal(m_Lua, "file_exists");  // stack +1
        lua_pushstring(m_Lua, name);  // stack +2
        lua_call(m_Lua, 1 , 1);  // stack +1
        result = lua_toboolean(m_Lua, 1);  // stack +1
        lua_pop(m_Lua, 1);  // stack 0
    }

    return result;
}

bool Model::generate_code(const char* language, const char* module_name)
{
    bool result = false;

    // Write header file
    lua_getglobal(m_Lua, "cgen");  // stack +1
    lua_getfield(m_Lua, 1, "write_header");  // stack +2
    if (module_name == NULL)
    {
        lua_pushstring(m_Lua, m_module_base_name->c_str());  // stack +3
    }
    else
    {
        lua_pushstring(m_Lua, module_name);  // stack +3
    }
    
    if (LUA_OK == lua_pcall(m_Lua, 1, 1, 0))  // stack +2
    {
        result = lua_toboolean(m_Lua, 2);
    }

    lua_pop(m_Lua, 2);  // stack 0

    // If failure at this point, don't bother continuing
    if (result != false)
    {
        result = write_c_source(module_name);
    }

    return result;
}

bool Model::initialize_interpreter(lua_State** L)
{
    bool result = false;
    *L = luaL_newstate();

    if (*L)
    {
        lua_gc(*L, LUA_GCSTOP, 0);
        luaL_openlibs(*L);
        lua_gc(*L, LUA_GCRESTART, 0);

        if (LUA_OK == luaL_dofile(*L, Model::main_script))
        {
            result = true;
        }
    }

    return result;
}

void Model::pushstring(const char* text)
{
    if (text == NULL)
    {
        lua_pushstring(m_Lua, "nil");
    }
    else
    {
        lua_pushstring(m_Lua, text);
    }
}

// Function pushes a table of integers on the Lua stack. Important: The stack
// is not empty when this function returns!
void Model::pushlocation(std::array<int, 4> position)
{
    lua_getglobal(m_Lua, "create_position");
    lua_pushinteger(m_Lua, position[0]);
    lua_pushinteger(m_Lua, position[1]);
    lua_pushinteger(m_Lua, position[2]);
    lua_pushinteger(m_Lua, position[3]);
    lua_call(m_Lua, 4, 1);  // One result at the top of the stack
}

void Model::reset_script()
{
    lua_getglobal(m_Lua, "reset");
    lua_call(m_Lua, 0, 0);
}

void Model::set_module_base_name()
{
    if (!m_diagram_file->empty())
    {
        std::size_t extension;
        m_module_base_name->assign(m_diagram_file->c_str());

        extension = m_module_base_name->rfind('.');
        if (extension != std::string::npos)
        {
            m_module_base_name->erase(extension);
        }
    }
}

/* May be used to write any text to a source file. Assumes source code generator
   is already on the Lua stack. */
bool Model::write_to_source(const char* text)
{
    bool result = true;

    lua_getfield(m_Lua, 1, "write_text");
    lua_pushstring(m_Lua, text);
    if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))
    {
        result = false;
        lua_pop(m_Lua, 1);
    }

    return result;
}

bool Model::write_state_tr_matrix(CState* cs)
{
    int nTr;  // number of transitions
    bool result;
    std::list<CTransition*> ct_list;
    std::list<CTransition*> cs_tr_list;
    CTransition** tr;

    ct_list = m_diagram->transition_list();
    result = true;

    lua_getfield(m_Lua, 1, "begin_tr_matrix");
    lua_pushstring(m_Lua, cs->name());
    if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))
    {
        result = false;
        lua_pop(m_Lua, 1);
    }

    // Select all transitions from the diagram which originate in cs
    for (auto iter = ct_list.begin(); iter != ct_list.end(); iter++)
    {
        if (m_diagram->transition_origin(*cs, **iter))
        {
            cs_tr_list.push_back(*iter);
        }
    }

    // Put transitions in an array for sorting
    nTr = cs_tr_list.size();
    if (nTr > 0)
    {
        int i = 0;
        tr = new CTransition*[nTr * sizeof(CTransition*)];

        // Copy list into array
        for (auto iter = cs_tr_list.begin(); iter != cs_tr_list.end(); iter++)
        {
            tr[i] = *iter;
            i++;
        }
        if (nTr > 1)
        {
            // Sort array
            std::qsort(tr, nTr, sizeof(CTransition*), CTransition::compare);
        }
    }

    for (int idx = 0; idx < nTr; idx++)
    {
        lua_getfield(m_Lua, 1, "tr_matrix_add");
        lua_pushstring(m_Lua, tr[idx]->name());
        if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))
        {
            result = false;
            lua_pop(m_Lua, 1);
        }
    }

    if (nTr > 0)
    {
        delete[] tr;
    }

    lua_getfield(m_Lua, 1, "end_tr_matrix");
    if (LUA_OK != lua_pcall(m_Lua, 0, 0, 0))
    {
        result = false;
        lua_pop(m_Lua, 1);
    }

    return result;
}

bool Model::write_c_source(const char* module_name)
{
    bool result;
    bool fileIsOpen = false;

    result = false;

    // Open source file
    lua_getglobal(m_Lua, "cgen");  // stack +1
    lua_getfield(m_Lua, 1, "open_src");  // stack +2
    if (module_name == NULL)
    {
        lua_pushstring(m_Lua, m_module_base_name->c_str());  // stack +3
    }
    else
    {
        lua_pushstring(m_Lua, module_name);  // stack +3
    }
    
    if (LUA_OK == lua_pcall(m_Lua, 1, 1, 0))  // stack +2
    {
        fileIsOpen = lua_toboolean(m_Lua, 2);
        lua_pop(m_Lua, 1);  // stack +1
    }
    else
    {
        lua_pop(m_Lua, 2);  // stack 0
        return false;  // No need to continue
    }

    result = true;

    if (fileIsOpen)
    {
        std::list<CState*> cs_list;
        std::list<CTransition*> ct_list;

        // Includes at the top of the file
        lua_getfield(m_Lua, 1, "includes");
        if (module_name == NULL)
        {
            lua_pushstring(m_Lua, m_module_base_name->c_str());  // stack +3
        }
        else
        {
            lua_pushstring(m_Lua, module_name);  // stack +3
        }

        if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))  // stack +1
        {
            result = false;  // stack +2
            lua_pop(m_Lua, 1);  // pop the error object
        }
        // stack +1

        // Prototypes (states)
        if(!write_to_source("\n/*--- State Action Prototypes ---*/\n"))
        {
            result = false;
        }
        cs_list = m_diagram->state_list();
        for (auto iter = cs_list.begin(); iter != cs_list.end(); iter++)
        {
            CState* cs = *iter;

            if (cs->during_action() != NULL)
            {
                if (0 != std::strcmp(cs->during_action(), "nil"))
                {
                    lua_getfield(m_Lua, 1, "action_proto");  // stack +2
                    lua_pushstring(m_Lua, cs->name());  // stack +3
                    lua_pushstring(m_Lua, during_suffix);  // stack +4
                    if (LUA_OK != lua_pcall(m_Lua, 2, 0, 0))  // stack +1
                    {
                        result = false;
                        lua_pop(m_Lua, 1);
                    }
                }
            }

            if (cs->entry_action() != NULL)
            {
                if (0 != std::strcmp(cs->entry_action(), "nil"))
                {
                    lua_getfield(m_Lua, 1, "action_proto");  // stack +2
                    lua_pushstring(m_Lua, cs->name());  // stack +3
                    lua_pushstring(m_Lua, entry_suffix);  // stack +4
                    if (LUA_OK != lua_pcall(m_Lua, 2, 0, 0))  // stack +1
                    {
                        result = false;
                        lua_pop(m_Lua, 1);
                    }
                }
            }
        }
        // Prototypes (transitions)
        if(!write_to_source("\n/*--- Transition Prototypes ---*/\n"))
        {
            result = false;
        }
        ct_list = m_diagram->transition_list();
        for (auto iter = ct_list.begin(); iter != ct_list.end(); iter++)
        {
            CTransition* ct = *iter;

            lua_getfield(m_Lua, 1, "transition_event_proto");  // stack +2
            lua_pushstring(m_Lua, ct->name());  // stack +3
            if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))  // stack +1
            {
                result = false;
                lua_pop(m_Lua, 1);
            }

            if (ct->action() != NULL)
            {
                if (0 != std::strcmp(ct->action(), "nil"))
                {
                    lua_getfield(m_Lua, 1, "action_proto");  // stack +2
                    lua_pushstring(m_Lua, ct->name());  // stack +3
                    lua_pushstring(m_Lua, t_action_suffix);  // stack +4
                    if (LUA_OK != lua_pcall(m_Lua, 2, 0, 0))  // stack +1
                    {
                        result = false;
                        lua_pop(m_Lua, 1);
                    }
                }
            }
        }

        if (!write_to_source("\n/*--- Transitions ---*/\n"))
        {
            result = false;
        }
        for (auto iter = ct_list.begin(); iter != ct_list.end(); iter++)
        {
            CTransition* ct = *iter;

            lua_getfield(m_Lua, 1, "declare_transition");  // stack +2
            lua_pushstring(m_Lua, ct->name());  // stack +3
            if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))  // stack +1
            {
                result = false;
                lua_pop(m_Lua, 1);
            }
        }

        if (!write_to_source("\n/*--- States ---*/\n"))
        {
            result = false;
        }
        for (auto iter = cs_list.begin(); iter != cs_list.end(); iter++)
        {
            CState* cs = *iter;

            lua_getfield(m_Lua, 1, "declare_state");  // stack +2
            lua_pushstring(m_Lua, cs->name());  // stack +3
            if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))  // stack +1
            {
                result = false;
                lua_pop(m_Lua, 1);
            }
        }

        if (!write_to_source("\n/*--- State Transition Matrices ---*/\n"))
        {
            result = false;
        }

        for (auto iter = cs_list.begin(); iter != cs_list.end(); iter++)
        {
            CState* cs = *iter;

            if (!write_state_tr_matrix(cs))
            {
                result = false;
            }
        }

        if (!write_to_source("/*--- Initialization ---*/\n"))
        {
            result = false;
        }

        lua_getfield(m_Lua, 1, "define_init_begin");
        lua_pushstring(m_Lua, m_module_base_name->c_str());
        if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))
        {
            result = false;
            lua_pop(m_Lua, 1);
        }

        for (auto iter = ct_list.begin(); iter != ct_list.end(); iter++)
        {
            CState* dest;
            CTransition* ct = *iter;

            lua_getfield(m_Lua, 1, "init_transition");  // stack +2
            lua_pushstring(m_Lua, ct->name());  // stack +3
            if (ct->action() == NULL)
            {
                lua_pushnil(m_Lua);  // stack +4
            }
            else if (std::strcmp(ct->action(), "nil") == 0)
            {
                lua_pushnil(m_Lua);  // stack +4
            }
            else
            {
                lua_pushstring(m_Lua, t_action_suffix);  // stack +4
            }
            dest = m_diagram->transition_dest(*ct);
            if (dest == NULL)
            {
                lua_pushnil(m_Lua);  // This is a diagram error, stack +5
            }
            else
            {
                lua_pushstring(m_Lua, dest->name());  // stack +5
            }
            if (LUA_OK != lua_pcall(m_Lua, 3, 0, 0))  // stack +1
            { 
                result = false;
                lua_pop(m_Lua, 1);
            }
        }

        if (!write_to_source("    /* initialize states */\n"))
        {
            result = false;
        }

        for (auto iter = cs_list.begin(); iter != cs_list.end(); iter++)
        {
            CState* parent;
            CState* cs = *iter;

            lua_getfield(m_Lua, 1, "init_state");  // stack +2
            lua_pushstring(m_Lua, cs->name());  // stack +3
            parent = m_diagram->state_parent(*cs);
            if (parent == NULL)
            {
                lua_pushnil(m_Lua);  // stack +4
            }
            else
            {
                lua_pushstring(m_Lua, parent->name());  // stack +4
            }
            if (cs->during_action() == NULL ||
                0 == std::strcmp(cs->during_action(), "nil"))
            {
                lua_pushnil(m_Lua);  // stack +5
            }
            else
            {
                lua_pushstring(m_Lua, during_suffix);  // stack +5
            }
            if (cs->entry_action() == NULL ||
                0 == std::strcmp(cs->entry_action(), "nil"))
            {
                lua_pushnil(m_Lua);  // stack +6
            }
            else
            {
                lua_pushstring(m_Lua, entry_suffix);  // stack +6
            }

            if (LUA_OK != lua_pcall(m_Lua, 4, 0, 0))  // stack +1
            {
                result = false;
                lua_pop(m_Lua, 1);
            }
        }

        // Close out the initialization function
        CState* start = m_diagram->starting_state();
        lua_getfield(m_Lua, 1, "complete_init_function");
        if (start == NULL)  // Diagram error
        {
            lua_pushnil(m_Lua);
        }
        else
        {
            lua_pushstring(m_Lua, start->name());
        }
        if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))
        {
            result = false;
            lua_pop(m_Lua, 1);
        }

        // Write out standard function definitions
        lua_getfield(m_Lua, 1, "write_selection_transition");
        if (LUA_OK != lua_pcall(m_Lua, 0, 0, 0))
        {
            result = false;
            lua_pop(m_Lua, 1);
        }
        lua_getfield(m_Lua, 1, "write_exec_entry");
        if (LUA_OK != lua_pcall(m_Lua, 0, 0, 0))
        {
            result = false;
            lua_pop(m_Lua, 1);
        }
        lua_getfield(m_Lua, 1, "write_exec_during");
        if (LUA_OK != lua_pcall(m_Lua, 0, 0, 0))
        {
            result = false;
            lua_pop(m_Lua, 1);
        }
        lua_getfield(m_Lua, 1, "write_step");
        lua_pushstring(m_Lua, m_module_base_name->c_str());
        if (LUA_OK != lua_pcall(m_Lua, 1, 0, 0))
        {
            result = false;
            lua_pop(m_Lua, 1);
        }

        // Write out event and transition action function definitions
        for (auto iter = ct_list.begin(); iter != ct_list.end(); iter++)
        {
            CTransition* ct = *iter;

            lua_getfield(m_Lua, 1, "transition_event_def");  // stack +2
            lua_pushstring(m_Lua, ct->name());  // stack +3
            if (m_diagram->no_text(ct->condition()))
            {
                lua_pushstring(m_Lua, "1");  // always return true
            }
            else
            {
                lua_pushstring(m_Lua, ct->condition());
            }
            if (LUA_OK != lua_pcall(m_Lua, 2, 0, 0))  // stack +1
            {
                result = false;
                lua_pop(m_Lua, 1);
            }

            if (m_diagram->no_text(ct->action()) == false)
            {
                lua_getfield(m_Lua, 1, "action_def");
                lua_pushstring(m_Lua, ct->name());
                lua_pushstring(m_Lua, t_action_suffix);
                lua_pushstring(m_Lua, ct->action());
                if (LUA_OK != lua_pcall(m_Lua, 3, 0, 0))
                {
                    result = false;
                    lua_pop(m_Lua, 1);
                }
            }
        }

        // Write out state action function definitions 
        for (auto iter = cs_list.begin(); iter != cs_list.end(); iter++)
        {
            CState* cs = *iter;

            if (m_diagram->no_text(cs->entry_action()) == false)
            {
                lua_getfield(m_Lua, 1, "action_def");
                lua_pushstring(m_Lua, cs->name());
                lua_pushstring(m_Lua, entry_suffix);
                lua_pushstring(m_Lua, cs->entry_action());
                if (LUA_OK != lua_pcall(m_Lua, 3, 0, 0))
                {
                    result = false;
                    lua_pop(m_Lua, 1);
                }
            }
            if (m_diagram->no_text(cs->during_action()) == false)
            {
                lua_getfield(m_Lua, 1, "action_def");
                lua_pushstring(m_Lua, cs->name());
                lua_pushstring(m_Lua, during_suffix);
                lua_pushstring(m_Lua, cs->during_action());
                if (LUA_OK != lua_pcall(m_Lua, 3, 0, 0))
                {
                    result = false;
                    lua_pop(m_Lua, 1);
                }
            }
        }
    }

    // Close source file
    if (fileIsOpen)
    {
        lua_getfield(m_Lua, 1, "close_src");  // stack +2
        if (LUA_OK == lua_pcall(m_Lua, 0, 0, 0))  // stack +1
        {
            lua_pop(m_Lua, 1);  // stack 0
        }
        else
        {
            lua_pop(m_Lua, 2);  // stack 0
            return false;
        }
    }

    return result;
}
