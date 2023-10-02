#include "diagram.h"

Diagram::Diagram()
{

}

Diagram::~Diagram()
{

}

void Diagram::add_state(CState* state)
{
    states.push_back(state);
}

void Diagram::add_transition(CTransition* transition)
{
    transitions.push_back(transition);
}

void Diagram::remove_state(CState* state)
{
    states.remove(state);
}

void Diagram::remove_transition(CTransition* transition)
{
    transitions.remove(transition);
}
