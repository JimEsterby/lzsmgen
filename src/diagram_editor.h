#ifndef DIAGRAM_EDITOR_H
#define DIAGRAM_EDITOR_H

#include <FL/Fl_Scroll.H>
#include "component_pict.h"

class DiagramEditor : public Fl_Scroll
{
private:
    ComponentPict* selected;
    bool m_changed;

public:
    DiagramEditor(int x, int y, int w, int h, const char* name = 0);
    void clear_selections();
    ComponentPict* selected_component() const { return selected; }
    void select_component(ComponentPict* cp);
    bool changed() const { return m_changed; }
    void set_changed() { m_changed = true; }
    void reset_changed() { m_changed = false; }

    // If component needs transparent area, it can use this color:
    static const int backcolor = 19;
};

#endif
