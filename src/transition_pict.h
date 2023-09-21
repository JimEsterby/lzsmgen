#ifndef TRANSITION_PICT_H
#define TRANSITION_PICT_H

#include "component_pict.h"

// Rendering (picture) of state machine transition
class TransitionPict : public ComponentPict
{
public:
    TransitionPict(int x, int y, int w, int h, const char* name = 0);
    void transition_resize(int x1, int y1, int x2, int y2);

protected:
    int handle(int event);
    void draw();
    void center(int* x, int* y) const;
    enum point_area { NA, cent, org, dest };

private:
    int x_org;
    int y_org;
    int x_dest;
    int y_dest;

    static const int margin = 5;
    double angle;  // degrees, NOT radians
    static const int arrow_head = 10;
    static const int grab_area = 10;

    int drag_area(int x, int y);

    // Standard distance formula
    static double distance(int x1, int y1, int x2, int y2);

};

#endif
