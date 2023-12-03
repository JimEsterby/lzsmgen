#include "viewer.h"
#include "model.h"
#include "file_callback.h"
#include "data_callback.h"

int main(int argc, char *argv[])
{
    int result;
    // Create the model
    theModel = new Model(argv[0]);
    // Create control interfaces for viewer use
    file_callback = new FileCallback;
    data_callback = new DataCallback;
    
    Viewer* view = open_viewer(argc, argv);

    result = view->run();

    delete file_callback;
    delete data_callback;
    delete theModel;

    return result;
}
