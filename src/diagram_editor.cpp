#include "diagram_editor.h"

DiagramEditor::DiagramEditor(int x, int y, int w, int h, const char* name)
: Fl_Scroll(x, y, w, h, name)
{
    color(backcolor);
    m_changed = false;
}

void DiagramEditor::clear_selections()
{
    int nComponents = children();

    for(int i = 0; i < nComponents; i++)
    {
        ComponentPict* cp = (ComponentPict*)child(i);
                      
        if (cp->is_selected())
        {
            cp->unselect();
            cp->redraw();
        }
    }
}

void DiagramEditor::select_component(ComponentPict* cp)
{
    if (selected)
    {
        selected->unselect();
        selected->redraw();
    }
    selected = cp;
    if (cp)
    {
        selected->select();
        selected->redraw();
    }
}
