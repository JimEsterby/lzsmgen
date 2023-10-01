#include "component_pict.h"
#include <FL/fl_draw.H>

ComponentPict::ComponentPict(int x, int y, int w, int h, const char* name)
: Fl_Widget(x, y, w, h, name)
{
}

void ComponentPict::select()
{
	set_flag(USERFLAG1);
}

void ComponentPict::unselect()
{
	clear_flag(USERFLAG1);
}

bool ComponentPict::is_selected() const
{
	bool result = false;
	unsigned int mask = flags();
	if ((mask & USERFLAG1) != 0)
	{
		result = true;
	}
	return result;
}

int ComponentPict::handle(int event)
{
	int result = 0;

	if (event == FL_ENTER || event == FL_LEAVE)
	{
		result = 1;
	}

	return result;
}

void ComponentPict::draw_selection_box(int x, int y, int dim, Fl_Color c)
{
	Fl_Color saved = fl_color();
	fl_color(c);

	fl_begin_line();
	fl_vertex(x - dim, y - dim);
	fl_vertex(x + dim, y - dim);
	fl_vertex(x + dim, y + dim);
	fl_vertex(x - dim, y + dim);
	fl_vertex(x - dim, y - dim);
	fl_end_line();

	fl_color(saved);  // Restore color
}

