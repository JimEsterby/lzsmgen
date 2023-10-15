#include "model.h"
extern "C" {
#include "lualib.h"
#include "lauxlib.h"
}
#include<cstdio>

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

    return result;
}

// Check if the file exists. Normally used to prevent overwriting a file if the
// user does not explicitly want to overwrite the file.
bool Model::file_exists(const char* name) const
{
    bool result;

    lua_getglobal(m_Lua, "file_exists");  // stack +1
    lua_pushstring(m_Lua, name);  // stack +2
    lua_call(m_Lua, 1 , 1);  // stack +1
    result = lua_toboolean(m_Lua, 1);  // stack +1
    lua_pop(m_Lua, 1);  // stack 0

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
