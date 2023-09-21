#ifndef DIAGRAM_EDITOR_H
#define DIAGRAM_EDITOR_H

#include <FL/Fl_Scroll.H>

class DiagramEditor : public Fl_Scroll
{
public:
    DiagramEditor(int x, int y, int w, int h, const char* name = 0);
    void clear_selections();

    // If component needs transparent area, it can use this color:
    static const int backcolor = 19;
};

#endif
