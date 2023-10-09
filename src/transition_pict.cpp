#include "transition_pict.h"
#include "diagram_editor.h"
#include "data_callback.h"
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include<cmath>
#include <FL/fl_ask.H>  // Temporary
#include "transition_dlg.h"

TransitionPict::TransitionPict(int x, int y, int w, int h, const char* condition)
: ComponentPict(x, y, w, h, condition)
{
    std::array<int, 4> position;
    labelsize(12);
    align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE);
    x_org = x + margin;
    y_org = y + margin;
    x_dest = x + w - margin;
    y_dest = y + h - margin;

    position[0] = x_org;
    position[1] = y_org;
    position[2] = x_dest;
    position[3] = y_dest;

    data = data_callback->create_transition(condition, position);
}

TransitionPict::~TransitionPict()
{
    data_callback->destroy_transition(data);
    delete data;
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
        else  // bottom to top
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
    static int orient = right;
    static int drag_type = NA;
    int ev_x;
    int ev_y;
    int x_center;
    int y_center;
    DiagramEditor* ed;
    int result = ComponentPict::handle(event);

    ev_x = Fl::event_x();
    ev_y = Fl::event_y();

    if (event == FL_ENTER)
    {
        // Clear the mouse clicks
        Fl::event_clicks(0);
    }

    if (FL_LEFT_MOUSE == Fl::event_button())
    {
        if (Fl::event_clicks())
        {
            Fl::event_clicks(0);
            TransitionDialog* td = new TransitionDialog(data);
            td->show();
            label(data->condition());
        }

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
            orient = direction();
            drag_type = drag_area(ev_x, ev_y);
            result = 1;
            break;

        case FL_RELEASE:
            // Clear the other selections in the parent editor
            ed = (DiagramEditor*)parent();
            ed->clear_selections();
            ed->select_component(this);
            result = 1;
            break;

        case FL_DRAG:
            if (drag_type == cent)
            {
                position(offset[0] + ev_x, offset[1] + ev_y);
                translate(orient);
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

            // Update data
            data->resize(x_org, y_org, x_dest, y_dest);
            result = 1;
            break;
        }
    }

    return result;
}

void TransitionPict::draw()
{
    int x_center;
    int y_center;

    // Clear selection boxes
    center(&x_center, &y_center);
    draw_selection_box(x_org, y_org, 2, parent()->color());
    draw_selection_box(x_center, y_center, 2, parent()->color());
    draw_selection_box(x_dest, y_dest, 2, parent()->color());

    draw_label();
    fl_begin_line();
    fl_vertex(x_org, y_org);
    fl_vertex(x_dest, y_dest);
    fl_end_line();
    draw_arrow();

    if (is_selected())
    {
        // Draw selection boxes
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

// Returns the direction that transition is pointing
// Uses the "border" enum
int TransitionPict::direction() const
{
    int result = right;

    // Is horizontal
    if (y_org == y_dest)
    {
        if (x_org > x_dest)  // right to left
        {
            result = left;
        }

        // else result = right
    }

    // Is vertical
    else if (x_org == x_dest)
    {
        if (y_dest > y_org)  // top to bottom
        {
            result = bottom;
        }
        else  // bottom to top
        {
            result = top;
        }
    }

    else if (x_dest > x_org && y_dest > y_org)  // point to lower right
    {
        result = bottom_right;
    }
    else if (x_dest > x_org && y_org > y_dest)  // point to upper right
    {
        result = top_right;
    }
    else if (x_org > x_dest && y_dest > y_org)  // point to lower left
    {
        result = bottom_left;
    }
    else  // assume point to upper left
    {
        result = top_left;
    }

    return result;
}

void TransitionPict::translate(int orientation)
{
    switch (orientation)
    {
    case right:
    case bottom:
    case bottom_right:
        x_org = x() + margin;
        y_org = y() + margin;
        x_dest = x() + w() - margin;
        y_dest = y() + h() - margin;
        break;

    case left:
    case top:
    case top_left:
        x_dest = x() + margin;
        y_dest = y() + margin;
        x_org = x() + w() - margin;
        y_org = y() + h() - margin;
        break;

    case top_right:
        x_org = x() + margin;
        y_org = y() + h() - margin;
        x_dest = x() + w() - margin;
        y_dest = y() + margin;
        break;

    case bottom_left:
        x_org = x() + w() - margin;
        y_org = y() + margin;
        x_dest = x() + margin;
        y_dest = y() + h() - margin;
        break;

    default:
        // do nothing
        break;
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
