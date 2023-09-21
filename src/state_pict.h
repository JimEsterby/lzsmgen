#ifndef STATE_PICT_H
#define STATE_PICT_H

#include "component_pict.h"

// GUI class represents a state picture
class StatePict : public ComponentPict
{
public:
    StatePict(int x, int y, int w, int h, const char* name = 0);
    StatePict(int x, int y, const char* name = 0);

protected:
    int handle(int event);
    void draw();
    int mouse_loc() const;

    static const int border_width = 15;  // 15 pixels
    static const int minimum_size = 45;
};

#endif
