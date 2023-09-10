#include <FL/Fl.H>
#include "viewer.h"

Viewer::Viewer()
{
    {
        topLevel = new Fl_Double_Window(360, 260, "State Machine Generator");
        topLevel->user_data((void*)(this));
        topLevel->end();
    } // Fl_Double_Window* topLevel
}

void Viewer::show(int argc, char *argv[])
{
    topLevel->show(argc, argv);
}

int Viewer::run()
{
    return Fl::run();
}

Viewer* open_viewer(int argc, char* argv[])
{
    Viewer* retval = new Viewer;

    Fl::visual(FL_DOUBLE | FL_INDEX);
    retval->show(argc, argv);

    return retval;
}
