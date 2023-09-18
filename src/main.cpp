#include "viewer.h"
#include "file_callback.h"
#include "data_callback.h"

int main(int argc, char *argv[])
{
    // Create control interfaces for viewer use
    file_callback = new FileCallback;
    data_callback = new DataCallback;
    
    Viewer* view = open_viewer(argc, argv);

    return view->run();
}
