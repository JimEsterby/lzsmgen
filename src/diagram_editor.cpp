#include "diagram_editor.h"

DiagramEditor::DiagramEditor(int x, int y, int w, int h, const char* name)
: Fl_Scroll(x, y, w, h, name)
{
    color(backcolor);
    m_changed = false;
    m_selected = 0;
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

    m_selected = 0;
}

void DiagramEditor::select_component(ComponentPict* cp)
{
    if (m_selected)
    {
        m_selected->unselect();
        m_selected->redraw();
    }
    m_selected = cp;
    if (cp)
    {
        m_selected->select();
        m_selected->redraw();
    }
}
