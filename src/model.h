#ifndef MODEL_H
#define MODEL_H

#include<string>
#include "diagram.h"
extern "C" {
#include "lua.h"
}

class Model
{
public:
    Model();
    Model(const char* file_name);
    ~Model();
    Diagram* diagram() const;
    bool file_loaded() const;
    const char* file_name() const;
    void file_name(const char* name);
    bool save_file();
    bool open_file(const char* name);
    bool file_exists(const char* name) const;
    bool io_failure() const { return failed_interpreter; }

private:
    Diagram* m_diagram;
    std::string* m_diagram_file;  // filename
    lua_State* m_Lua;  // Lua interpreter
    bool failed_interpreter;  // will not be able to read/write files
    static bool initialize_interpreter(lua_State** L);

    void pushstring(const char* text);
    void pushlocation(std::array<int, 4> position);
};

extern Model* theModel;

#endif
