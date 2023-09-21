#include "diagram_editor.h"
#include "component_pict.h"

DiagramEditor::DiagramEditor(int x, int y, int w, int h, const char* name)
: Fl_Scroll(x, y, w, h, name)
{
    color(backcolor);
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
