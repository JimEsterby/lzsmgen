#include "viewer.h"

int main(int argc, char *argv[])
{
    Viewer* view = open_viewer(argc, argv);

    return view->run();
}
