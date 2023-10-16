#ifndef FILE_CALLBACK_H
#define FILE_CALLBACK_H

// Controller for file operations
// Interface for GUI
class FileCallback
{
public:
    FileCallback();
    ~FileCallback();


    bool open(const char* file_name);
    bool check_preexisting(const char* file_name) const;
    bool loaded() const;  // A diagram file is loaded
    const char* name() const;  // file name
    bool save();
    bool save(const char* name);
};

// The controller will create this for viewer use
extern FileCallback* file_callback;

#endif
