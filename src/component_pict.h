#ifndef COMPONENT_PICT_H
#define COMPONENT_PICT_H

#include <FL/Fl_Widget.H>

// Component picture class
// Base class of components in a DiagramEditor
class ComponentPict : public Fl_Widget
{
public:
    ComponentPict(int x, int y, int w, int h, const char* name = 0);
    virtual int handle(int event);

    void select();
    void unselect();
    bool is_selected() const;

protected:
    enum border{ top_left,    top,    top_right,
                 left,        center, right,
                 bottom_left, bottom, bottom_right };

    void draw_selection_box(int x, int y, int dim, Fl_Color c);
};

#endif
