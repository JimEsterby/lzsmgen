#ifndef viewer_h
#define viewer_h

#include <FL/Fl_Double_Window.H>

class Viewer
{
public:
    Viewer();
    void show(int argc, char *argv[]);
    int run();

private:
    Fl_Double_Window *topLevel;
};

Viewer* open_viewer(int argc, char* argv[]);

#endif
