#include "model.h"
extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}
#include<cstdio>

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

Model::Model()
{
    m_diagram = new Diagram;
    m_diagram_file = new std::string;

    // Attempt to start the interpreter
    failed_interpreter = initialize_interpreter(&m_Lua) ? false : true;
}

Model::Model(const char* file_name)
{
    m_diagram = new Diagram;
    m_diagram_file = new std::string(file_name);

    // Attempt to start the interpreter
    failed_interpreter = initialize_interpreter(&m_Lua) ? false : true;
}

Model::~Model()
{
    delete m_diagram;
    delete m_diagram_file;
    lua_close(m_Lua);
}

Diagram* Model::diagram() const
{
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

        std::printf("S=%d\tT=%d\n",nr_states,nr_transitions);

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

        m_diagram_file->assign(name);
        result = true;
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
    if (LUA_OK == lua_pcall(m_Lua, 1, 1, 0))
    {
        result = lua_toboolean(m_Lua, 1);
        lua_pop(m_Lua, 1);
    }

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

bool Model::initialize_interpreter(lua_State** L)
{
    bool result = false;
    *L = luaL_newstate();

    if (*L)
    {
        lua_gc(*L, LUA_GCSTOP, 0);
        luaL_openlibs(*L);
        lua_gc(*L, LUA_GCRESTART, 0);

        if (LUA_OK == luaL_dofile(*L, "lzsmgen.lua"))
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
