#ifndef STATE_PICT_H
#define STATE_PICT_H

#include <FL/Fl_Box.H>

class StatePict : public Fl_Box
{
public:
    StatePict(int x, int y, int w, int h, const char* name = 0);

protected:
    int handle(int event);
    void draw();

private:

};

#endif
