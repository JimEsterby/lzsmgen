#include "state_pict.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>

StatePict::StatePict(int x, int y, int w, int h, const char* name)
: Fl_Box(x, y, w, h, name)
{
    box(FL_ROUNDED_BOX);
    align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
    color((Fl_Color)215);  // light yellow
    labelsize(12);
}

int StatePict::handle(int event)
{
    static int offset[2] = { 0, 0 };
    int result = Fl_Box::handle(event);

    switch (event)
    {
    case FL_PUSH:
        offset[0] = x() - Fl::event_x();
        offset[0] = y() - Fl::event_y();
        result = 1;
        break;

    case FL_RELEASE:
        result = 1;
        break;

    case FL_DRAG:
        position(offset[0] + Fl::event_x(), offset[1] + Fl::event_y());
        ((Fl_Window*)parent())->redraw();
        result = 1;
    }

    return result;
}

void StatePict::draw()
{
    Fl_Box::draw();

    fl_line(x(), y() + fl_height(), x() + w(), y() + fl_height());
}
