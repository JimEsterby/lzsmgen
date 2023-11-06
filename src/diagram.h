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
    std::list<CState*> state_list() const { return states; }
    std::list<CTransition*> transition_list() const { return transitions; }
    int state_count() const;
    int transition_count() const;
    bool transition_origin(const CState& state, const CTransition& transition) const;
    CState* transition_dest(const CTransition& transition);
};

#endif
