#include "state_pict.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include "diagram_editor.h"
#include "data_callback.h"
#include "state_dlg.h"

StatePict::StatePict(int x, int y, int w, int h, const char* name)
: ComponentPict(x, y, w < minimum_size? minimum_size : w, h < minimum_size? minimum_size : h, name)
{
	std::array<int, 4> position;
    box(FL_ROUNDED_BOX);
    align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
    color((Fl_Color)215);  // light yellow
    labelsize(12);

	position[0] = x;
	position[1] = y;
	position[2] = x + w;
	position[3] = y + h;

	data = data_callback->create_state(name, position);
}

StatePict::StatePict(int x, int y, const char* name)
: ComponentPict(x, y, minimum_size, minimum_size, name)
{
	std::array<int, 4> position;
    box(FL_ROUNDED_BOX);
    align(Fl_Align(FL_ALIGN_TOP|FL_ALIGN_INSIDE));
    color((Fl_Color)215);  // light yellow
    labelsize(12);

	position[0] = x;
	position[1] = y;
	position[2] = x + minimum_size;
	position[3] = y + minimum_size;

	data = data_callback->create_state(name, position);
}

StatePict::~StatePict()
{
	data_callback->destroy_state(data);
	delete data;
}

int StatePict::handle(int event)
{
    static int offset[2] = { 0, 0 };
    static int rect[4] = { 0, 0, 0, 0 };
    static int loc = center;
    int ev_x;
    int ev_y;
    int result = ComponentPict::handle(event);
	DiagramEditor* ed = (DiagramEditor*)parent();

    ev_x = Fl::event_x();
    ev_y = Fl::event_y();

	if (event == FL_ENTER)
	{
		// Clear mouse click events
		Fl::event_clicks(0);

		// Adjust cursor based on mouse location
		(void)mouse_loc();
	}

	else if (event == FL_MOVE)
	{
		(void)mouse_loc();
	}

	else if (event == FL_LEAVE)
	{
		fl_cursor(FL_CURSOR_DEFAULT);
	}

    if (FL_LEFT_MOUSE == Fl::event_button())
    {
		if (Fl::event_clicks())
		{
			Fl::event_clicks(0);
			StateDialog* sd = new StateDialog(data);
			sd->show();
			if (sd->OK_pressed())
			{
				label(data->name());
				ed->set_changed();
			}
			delete sd;
		}

	    switch (event)
	    {
	    case FL_PUSH:
	        loc = mouse_loc();
	        offset[0] = x() - ev_x;
	        offset[0] = y() - ev_y;
	        rect[0] = x();
	        rect[1] = y();
	        rect[2] = x() + w();
	        rect[3] = y() + h();
	        result = 1;
	        break;
	
	    case FL_RELEASE:
            // Clear the other selections in the parent editor
			ed->clear_selections();
			ed->select_component(this);
            fl_cursor(FL_CURSOR_DEFAULT);

	        result = 1;
	        break;
	
	    case FL_DRAG:
	        // This is code necessary to handling all of the resizing possibilities
	        // while maintaining a minimum dimensions for the component
			ed->select_component(this);
	        switch (loc)
	        {
	        case top:
	            if (rect[3] - ev_y >= minimum_size)
	            {
	                resize(rect[0], ev_y, rect[2] - rect[0], rect[3] - ev_y);
	            }
	            break;
	        case bottom:
	            if (ev_y - rect[1] >= minimum_size)
	            {
	                resize(rect[0], rect[1], rect[2] - rect[0], ev_y - rect[1]);
	            }
	            break;
	        case left:
	            if (rect[2] - ev_x >= minimum_size)
	            {
	                resize(ev_x, rect[1], rect[2] - ev_x, rect[3] - rect[1]);
	            }
	            break;
	        case right:
	            if (ev_x - rect[0] >= minimum_size)
	            {
	                resize(rect[0], rect[1], ev_x - rect[0], rect[3] - rect[1]);
	            }
	            break;
	        case top_left:
	            if (rect[2] - ev_x >= minimum_size && rect[3] - ev_y >= minimum_size)
	            {
	                resize(ev_x, ev_y, rect[2] - ev_x, rect[3] - ev_y);
	            }
	            else if (rect[2] - ev_x >= minimum_size)
	            {
	                resize(ev_x, ev_y, rect[2] - ev_x, minimum_size);
	            }
	            else if (rect[3] - ev_y >= minimum_size)
	            {
	                resize(ev_x, ev_y, minimum_size, rect[3] - ev_y);
	            }
	            break;
	        case bottom_left:
	            if (rect[2] - ev_x >= minimum_size && ev_y - rect[1] >= minimum_size)
	            {
	                resize(ev_x, rect[1], rect[2] - ev_x, ev_y - rect[1]);
	            }
	            else if (rect[2] - ev_x >= minimum_size)
	            {
	                resize(ev_x, rect[1], rect[2] - ev_x, minimum_size);
	            }
	            else if (ev_y - rect[1] >= minimum_size)
	            {
	                resize(ev_x, rect[1], minimum_size, ev_y - rect[1]);
	            }
	            break;
	        case top_right:
	            if (ev_x - rect[0] >= minimum_size && rect[3] - ev_y >= minimum_size)
	            {
	                resize(rect[0], ev_y, ev_x - rect[0], rect[3] - ev_y);
	            }
	            else if (ev_x - rect[0] >= minimum_size)
	            {
	                resize(rect[0], ev_y, ev_x - rect[0], minimum_size);
	            }
	            else if (rect[3] - ev_y >= minimum_size)
	            {
	                resize(rect[0], ev_y, minimum_size, rect[3] - ev_y);
	            }
	            break;
	        case bottom_right:
	            if (ev_x - rect[0] >= minimum_size && ev_y - rect[1] >= minimum_size)
	            {
	                resize(rect[0], rect[1], ev_x - rect[0], ev_y - rect[1]);
	            }
	            else if (ev_x - rect[0] >= minimum_size)
	            {
	                resize(rect[0], rect[1], ev_x - rect[0], minimum_size);
	            }
	            else if (ev_y - rect[1] >= minimum_size)
	            {
	                resize(rect[0], rect[1], minimum_size, ev_y - rect[1]);
	            }
	            break;
	
	        // Not resizing, just moving
	        case center:  // move
	            position(offset[0] + Fl::event_x(), offset[1] + Fl::event_y());
	            break;
	        }
	
	        ed->redraw();
			data->resize(x(), y(), x() + w(), y() + h());
			ed->set_changed();
	        result = 1;
	    }
    }

    return result;
}

void StatePict::draw()
{
	// erase selection rectangle
	Fl_Color c = fl_color();
	fl_rect(x(), y(), w(), h(), this->parent()->color());
	fl_color(c);

	draw_box();
	draw_label();

    fl_line(x(), y() + fl_height(), x() + w(), y() + fl_height());

	if (is_selected())
	{
        Fl_Color c = fl_color();
		fl_rect(x(), y(), w(), h(), FL_RED);
        fl_color(c);  // Restore
	}
}

// Determines location of mouse within the state picture
int StatePict::mouse_loc() const
{
    int result = center;

    // Mouse coordinates within the StatePict parent window
    int m_x;
    int m_y;

    m_x = Fl::event_x();
    m_y = Fl::event_y();

    if (m_x < x() + border_width)  // Close to the left
    {
        if (m_y < y() + border_width)  // Close to the top
        {
            result = top_left;
            fl_cursor(FL_CURSOR_NWSE);
        }
        else if (m_y > y() + h() - border_width)  // Close to bottom
        {
            result = bottom_left;
            fl_cursor(FL_CURSOR_NESW);
        }
        else  // (Center) left
        {
            result = left;
            fl_cursor(FL_CURSOR_WE);
        }
    }
    else if (m_x > x() + w() - border_width)  // Close to the right
    {
        if (m_y < y() + border_width)  // Close to the top
        {
            result = top_right;
            fl_cursor(FL_CURSOR_NESW);
        }
        else if (m_y > y() + h() - border_width)  // Close to the bottom
        {
            result = bottom_right;
            fl_cursor(FL_CURSOR_NWSE);
        }
        else  // (Center) right
        {
            result = right;
            fl_cursor(FL_CURSOR_WE);
        }
    }
    else if (m_y < y() + border_width)
    {
        result = top;
        fl_cursor(FL_CURSOR_NS);
    }
    else if (m_y > y() + h() - border_width)
    {
        result = bottom;
        fl_cursor(FL_CURSOR_NS);
    }
    else
    {
        fl_cursor(FL_CURSOR_MOVE);
    }

    return result;
}
