#ifndef STATE_PICT_H
#define STATE_PICT_H

#include <FL/Fl_Box.H>

// GUI class represents a state picture
class StatePict : public Fl_Box
{
public:
    StatePict(int x, int y, int w, int h, const char* name = 0);
    StatePict(int x, int y, const char* name = 0);

protected:
    int handle(int event);
    void draw();
    int mouse_loc() const;

    enum border{ top_left,    top,    top_right,
                 left,        center, right,
                 bottom_left, bottom, bottom_right };

    static const int border_width = 15;  // 15 pixels
    static const int minimum_size = 45;

private:

};

#endif
