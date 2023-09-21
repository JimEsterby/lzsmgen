#include "component_pict.h"

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
