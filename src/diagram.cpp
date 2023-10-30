#include "diagram.h"

Diagram::Diagram()
{

}

Diagram::~Diagram()
{
    int nStates = state_count();

    for (int idx = 0; idx < nStates; idx++)
    {
        auto iter = states.begin();
        CState* cs = *iter;
        states.pop_front();
        delete cs;
    }

    for (int idx = 0; idx < nStates; idx++)
    {
        auto iter = transitions.begin();
        CTransition* ct = *iter;
        transitions.pop_front();
        delete ct;
    }
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

/* Return the number of states in the diagram */
int Diagram::state_count() const
{
    int result = 0;
    for (auto iter = states.begin(); iter != states.end(); iter++)
    {
        result++;
    }

    return result;
}

/* Return the number of transitions in the diagram */
int Diagram::transition_count() const
{
    int result = 0;
    for (auto iter = transitions.begin(); iter != transitions.end(); iter++)
    {
        result++;
    }

    return result;
}

