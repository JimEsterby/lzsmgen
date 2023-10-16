#include "file_callback.h"
#include "model.h"

FileCallback* file_callback;  // THE file callback object

FileCallback::FileCallback()
{

}

FileCallback::~FileCallback()
{

}

/* Method for opening a diagram file */
bool FileCallback::open(const char* file_name)
{
    // Need to call "Model" code
    return theModel->open_file(file_name);
}

// Check if file already exists
bool FileCallback::check_preexisting(const char* file_name) const
{
    return theModel->file_exists(file_name);
}

bool FileCallback::loaded() const
{
    return theModel->file_loaded();
}

const char* FileCallback::name() const
{
    return theModel->file_name();
}

bool FileCallback::save()
{
    return theModel->save_file();
}

bool FileCallback::save(const char* name)
{
    theModel->file_name(name);
    return save();
}

