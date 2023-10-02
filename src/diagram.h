#ifndef DIAGRAM_H
#define DIAGRAM_H

#include "cstate.h"
#include "ctransition.h"
#include<list>

// Data class "diagram"
class Diagram
{
private:
    std::list<CState*>states;
    std::list<CTransition*>transitions;

public:
    Diagram();
    ~Diagram();
    void add_state(CState* state);
    void add_transition(CTransition* transition);
    void remove_state(CState* state);
    void remove_transition(CTransition* transition);
};

#endif
