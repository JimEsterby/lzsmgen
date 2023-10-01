#include "transition_pict.h"
#include "diagram_editor.h"
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include<cmath>

TransitionPict::TransitionPict(int x, int y, int w, int h, const char* name)
: ComponentPict(x, y, w, h, name)
{
    x_org = x + margin;
    y_org = y + margin;
    x_dest = x + w - margin;
    y_dest = y + h - margin;
}

void TransitionPict::transition_resize(int x1, int y1, int x2, int y2)
{
    // Set up rectangle according to the line parameters
    // Is horizontal
    if (y1 == y2)
    {
        if (x2 > x1)  // left to right
        {
            resize(x1 - margin, y1 - margin, x2 - x1 + margin * 2, margin * 2);
        }
        else  // right to left
        {
            resize(x2 - margin, y2 - margin, x1 - x2 + margin * 2, margin * 2);
        }
    }
    // Is vertical
    else if (x1 == x2)
    {
        if (y2 > y1)  // top to bottom
        {
            resize(x1 - margin, y1 - margin, margin * 2, y2 - y1 + margin * 2);
        }
        else  // right to left
        {
            resize(x2 - margin, y2 - margin, margin * 2, y1 - y2 + margin * 2);
        }
    }
    else if (x2 > x1 && y2 > y1)  // point to lower right
    {
        resize(x1 - margin, y1 - margin, x2 - x1 + 2 * margin, y2 - y1 + 2 * margin);
    }
    else if (x2 > x1 && y1 > y2)  // point to upper right
    {
        resize(x1 - margin, y2 - margin, x2 - x1 + 2 * margin, y1 - y2 + 2 * margin);
    }
    else if (x1 > x2 && y2 > y1)  // point to lower left
    {
        resize(x2 - margin, y1 - margin, x1 - x2 + 2 * margin, y2 - y1 + 2 * margin);
    }
    else  // assume point to upper left
    {
        resize(x2 - margin, y2 - margin, x1 - x2 + 2 * margin, y1 - y2 + 2 * margin);
    }
}

int TransitionPict::handle(int event)
{
    static int offset[2] = { 0, 0 };
    static int rect[4] = { 0, 0, 0, 0 };
    static int drag_type = NA;
    int ev_x;
    int ev_y;
    int x_center;
    int y_center;
    DiagramEditor* ed;
    int result = ComponentPict::handle(event);

    ev_x = Fl::event_x();
    ev_y = Fl::event_y();

    if (FL_LEFT_MOUSE == Fl::event_button())
    {	
        switch (event)
        {
        case FL_PUSH:
            center(&x_center, &y_center);
            offset[0] = x_center - ev_x;
            offset[0] = y_center - ev_y;
            rect[0] = x_org;
            rect[1] = y_org;
            rect[2] = x_dest;
            rect[3] = y_dest;
            drag_type = drag_area(ev_x, ev_y);
            result = 1;
            break;

        case FL_RELEASE:
            // Clear the other selections in the parent editor
            ed = (DiagramEditor*)parent();
            ed->select_component(this);
            result = 1;
            break;

        case FL_DRAG:
            if (drag_type == cent)
            {
                position(offset[0] + ev_x, offset[1] + ev_y);
                transition_resize(rect[0] + offset[0] + ev_x,
                                  rect[1] + offset[1] + ev_y,
                                  rect[2] + offset[0] + ev_x,
                                  rect[3] + offset[1] + ev_y);

                x_org = rect[0] + offset[0] + ev_x;
                y_org = rect[1] + offset[1] + ev_y;
                x_dest = rect[2] + offset[0] + ev_x;
                y_dest = rect[3] + offset[1] + ev_y;
            }
            else if (drag_type == org)
            {
                x_org = ev_x; y_org = ev_y; x_dest = rect[2]; y_dest = rect[3];
                transition_resize(ev_x, ev_y, rect[2], rect[3]);
            }
            else if (drag_type == dest)
            {
                x_org = rect[0]; y_org = rect[1]; x_dest = ev_x; y_dest = ev_y;
                transition_resize(rect[0], rect[1], ev_x, ev_y);
            }

            ((Fl_Window*)parent())->redraw();
            result = 1;
            break;
        }
    }

    return result;
}

void TransitionPict::draw()
{
    draw_label();
    fl_begin_line();
    fl_vertex(x_org, y_org);
    fl_vertex(x_dest, y_dest);
    fl_end_line();
    draw_arrow();

    if (is_selected())
    {
        int x_center;
        int y_center;

        center(&x_center, &y_center);

        // Little red box around the origin of the transition
        draw_selection_box(x_org, y_org, 2, FL_RED);
        draw_selection_box(x_center, y_center, 2, FL_RED);
        draw_selection_box(x_dest, y_dest, 2, FL_RED);
    }
}

void TransitionPict::center(int* x, int* y) const
{
    // y coordinate
    if (y_dest > y_org)
    {
        *y = (y_dest - y_org)/2 + y_org;
    }
    else
    {
        *y = (y_org - y_dest)/2 + y_dest;
    }

    // x coordinate
    if (x_dest > x_org)
    {
        *x = (x_dest - x_org)/2 + x_org;
    }
    else
    {
        *x = (x_org - x_dest)/2 + x_dest;
    }
}

int TransitionPict::drag_area(int x, int y)
{
    int x_center;
    int y_center;
    int result = 0;
    double threshold = grab_area;

    // Get the center point
    center(&x_center, &y_center);

    if (distance(x, y, x_dest, y_dest) < threshold/2.0)
    {
        result = dest;
        if (is_selected()) fl_cursor(FL_CURSOR_MOVE);
    }

    else if (distance(x, y, x_org, y_org) < threshold/2.0)
    {
        result = org;
        if (is_selected()) fl_cursor(FL_CURSOR_MOVE);
    }

    else if (distance(x, y, x_center, y_center) < threshold/2.0)
    {
        result = cent;  // Move
    }
    else
    {
        fl_cursor(FL_CURSOR_DEFAULT);
    }

    return result;
}

void TransitionPict::draw_arrow()
{
    if (x_org == x_dest)  // vertical
    {
        fl_begin_line();
        if (y_org > y_dest)
        {
            fl_vertex(x_dest - arrow_head/2, y_dest + (86 * arrow_head)/100);
            fl_vertex(x_dest, y_dest);
            fl_vertex(x_dest + arrow_head/2, y_dest + (86 * arrow_head)/100);
        }
        else
        {
            fl_vertex(x_dest + arrow_head/2, y_dest - (86 * arrow_head)/100);
            fl_vertex(x_dest, y_dest);
            fl_vertex(x_dest - arrow_head/2, y_dest - (86 * arrow_head)/100);
        }
        fl_end_line();
    }

    else if (y_org == y_dest)  // horizontal
    {
        fl_begin_line();
        if (x_org > x_dest)  // 180 degrees
        {
            fl_vertex(x_dest + (86 * arrow_head)/100, y_dest + arrow_head/2);
            fl_vertex(x_dest, y_dest);
            fl_vertex(x_dest + (86 * arrow_head)/100, y_dest - arrow_head/2);
        }
        else  // 0 degrees
        {
            fl_vertex(x_dest - (86 * arrow_head)/100, y_dest + arrow_head/2);
            fl_vertex(x_dest, y_dest);
            fl_vertex(x_dest - (86 * arrow_head)/100, y_dest - arrow_head/2);
        }
        fl_end_line();
    }

    else
    {
        double x_offset = -x_dest;
        double y_offset = -y_dest;

        // Put destination at (0, 0)
        double x_org_0 = x_org + x_offset;
        double y_org_0 = y_org + y_offset;
        double radians = std::atan2(y_org_0, x_org_0);
        x_org_0 = arrow_head * std::cos(radians);
        y_org_0 = arrow_head * std::sin(radians);
        // angle of the arrow head is 60 degrees
        double sin30 = std::sin(0.5236);  // 0.5236 = 30 degrees
        double cos30 = std::cos(0.5236);
        double sin_m30 = std::sin(-0.5236);
        double cos_m30 = std::cos(-0.5236);
        double x_arr1_0 = x_org_0 * cos30 - y_org_0 * sin30;
        double y_arr1_0 = y_org_0 * cos30 + x_org_0 * sin30;
        double x_arr2_0 = x_org_0 * cos_m30 - y_org_0 * sin_m30;
        double y_arr2_0 = y_org_0 * cos_m30 + x_org_0 * sin_m30;

        // Take the offset back out
        double x_arr1 = x_arr1_0 - x_offset;
        double y_arr1 = y_arr1_0 - y_offset;
        double x_arr2 = x_arr2_0 - x_offset;
        double y_arr2 = y_arr2_0 - y_offset;

        fl_begin_line();
        fl_vertex((int)round(x_arr1), (int)round(y_arr1));
        fl_vertex(x_dest, y_dest);
        fl_vertex((int)round(x_arr2), (int)round(y_arr2));
        fl_end_line();
    }
}

double TransitionPict::distance(int x1, int y1, int x2, int y2)
{
    double result;

    // prevent square root of zero
    if ((x2 - x1) == 0 && (y2 - y1) == 0)
    {
        result = 0.0;
    }
    else
    {
        double xd1 = x1;
        double yd1 = y1;
        double xd2 = x2;
        double yd2 = y2;

        result = std::sqrt((xd2 - xd1) * (xd2 - xd1) + (yd2 - yd1) * (yd2 - yd1) );
    }

    return result; 
}
