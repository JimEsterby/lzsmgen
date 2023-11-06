#include "diagram.h"

Diagram::Diagram()
{

}

Diagram::~Diagram()
{
    int nStates = state_count();
    int nTransitions = transition_count();

    for (int idx = 0; idx < nStates; idx++)
    {
        auto iter = states.begin();
        CState* cs = *iter;
        states.pop_front();
        delete cs;
    }

    for (int idx = 0; idx < nTransitions; idx++)
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

/*
   Returns true if transition originates from state.
   The basic idea is that the transition originates with the state if its
   start point is within the state, but not within a substate of the state.
*/
bool Diagram::transition_origin(const CState& state, const CTransition& transition) const
{
    bool result;
    int x, y;  // point of origin for the transition

    x = transition.position()[0];
    y = transition.position()[1];
    result = false;

    if (state.contains(x, y))
    {
        result = true;
        for (auto iter = states.begin(); iter != states.end(); iter++)
        {
            if (state.contains(**iter))
            {
                if ((*iter)->contains(x, y))
                {
                    result = false;
                }
            }
        }
    }

    return result;
}

//TODO:
CState* Diagram::transition_dest(const CTransition& transition)
{
    int x, y;
    CState* result = NULL;

    x = transition.position()[2];
    y = transition.position()[3];

    for (auto iter = states.begin(); iter != states.end(); iter++)
    {
        if ((*iter)->contains(x, y))
        {
            result = *iter;
        }
    }

    return result;
}

