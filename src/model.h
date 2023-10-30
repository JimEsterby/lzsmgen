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

    // Returns true if a model file is loaded
    bool file_loaded() const;

    // Returns the loaded diagram file name
    const char* file_name() const;

    // Returns the default name of a generated code file (w/o extension)
    const char* module_name() const;

    // Assigns a name to the diagram file
    void file_name(const char* name);

    // Save the diagram file
    bool save_file();

    // Open a diagram file
    bool open_file(const char* name);

    // Checks for the existence of a file
    bool file_exists(const char* name) const;

    bool generate_code(const char* language, const char* module_name = NULL);

    // Checks that the embedded Lua interpreter is operational
    bool io_failure() const { return failed_interpreter; }

private:
    Diagram* m_diagram;
    std::string* m_diagram_file;  // filename
    std::string* m_module_base_name;  // filename of generated code file(s) without extension
    lua_State* m_Lua;  // Lua interpreter
    bool failed_interpreter;  // will not be able to read/write files
    static const char* main_script;
    static bool initialize_interpreter(lua_State** L);

    void pushstring(const char* text);
    void pushlocation(std::array<int, 4> position);
    void reset_script();  // Reset script globals
    void set_module_base_name();
};

extern Model* theModel;

#endif
