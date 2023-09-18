#ifndef FILE_CALLBACK_H
#define FILE_CALLBACK_H

#include "diagram.h"

// Controller for file operations
// Interface for GUI
class FileCallback
{
public:
    FileCallback();
    ~FileCallback();


    bool open_file_request(const char* file_name);
};

// The controller will create this for viewer use
extern FileCallback* file_callback;

#endif
