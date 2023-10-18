#ifndef TRANSITION_PICT_H
#define TRANSITION_PICT_H

#include "component_pict.h"
#include<array>

class CTransition;

// Rendering (picture) of state machine transition
class TransitionPict : public ComponentPict
{
public:
    TransitionPict(int x, int y, int w, int h, const char* condition = "event");
    TransitionPict(CTransition* ct);
    virtual ~TransitionPict();
    void transition_resize(int x1, int y1, int x2, int y2);

protected:
    int handle(int event);
    void draw();
    void center(int* x, int* y) const;
    virtual int direction() const;
    virtual void translate(int orientation);
    enum point_area { NA, cent, org, dest };

private:
    int x_org;
    int y_org;
    int x_dest;
    int y_dest;

    CTransition* data;  // data access

    static const int margin = 5;
    static const int arrow_head = 10;
    static const int grab_area = 10;

    int drag_area(int x, int y);
    void draw_arrow();

    // Standard distance formula
    static double distance(int x1, int y1, int x2, int y2);

    // Calculate screen dimensions from CTransition information
    static int upper_left_x(std::array<int, 4> ct_pos);
    static int upper_left_y(std::array<int, 4> ct_pos);
    static int width(std::array<int, 4> ct_pos);
    static int height(std::array<int, 4> ct_pos);

};

#endif
