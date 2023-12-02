#ifndef STATE_PICT_H
#define STATE_PICT_H

#include "component_pict.h"
#include "cstate.h"

// GUI class represents a state picture
class StatePict : public ComponentPict
{
public:
    StatePict(int x, int y, int w, int h, const char* name = "state");
    StatePict(int x, int y, const char* name = 0);
    StatePict(CState* cs);
    virtual ~StatePict();

protected:
    int handle(int event);
    void draw();
    int mouse_loc() const;

    static const int border_width = 15;  // 15 pixels
    static const int minimum_size = 45;

private:
    CState* data;
    static const int fontsize = 10;
    static const int bg_color = 215;
};

#endif
