#include "diagram.h"
#include<cstring>

Diagram::Diagram()
{
    m_error = false;
    m_dependencies = new std::string();
    m_internals = new std::string();
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

    delete m_dependencies;
    delete m_internals;
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

// Find the destination state of a transition. If the transition has no
// destination, returns NULL
CState* Diagram::transition_dest(const CTransition& transition)
{
    int x, y;
    std::list<CState*> cs;
    CState* result = NULL;

    x = transition.position()[2];
    y = transition.position()[3];

    // Get list of states where transition ends. (There may be multiples
    // when states are substates of other states.)
    for (auto iter = states.begin(); iter != states.end(); iter++)
    {
        if ((*iter)->contains(x, y))
        {
            cs.push_back(*iter);
        }
    }

    if (cs.size() > 1)
    {
        // Copy list into array
        int idx;
        CState** cs_array = new CState*[cs.size() * sizeof(CState*)];
        idx = 0;
        for (auto iter = cs.begin(); iter != cs.end(); iter++)
        {
            cs_array[idx] = *iter;
            idx++;
        }
        // Sort array
        std::qsort(cs_array, cs.size(), sizeof(cs_array[0]), CState::compare);
        result = cs_array[0];
        delete[] cs_array;
    }
    else if (cs.size() == 1)
    {
        result = *cs.begin();
    }
    else
    {
        // Transition does not end in a state
        m_error = true;
    }

    if (result != NULL)
    {
        result = find_default_substate(result);
    }

    return result;
}

// Find the immediate parent of a given state. (The given state is a substate
// of the parent.) Returns NULL if the state is a top level with no parent.
CState* Diagram::state_parent(const CState& state) const
{
    std::list<CState*> parents;
    CState* result = NULL;

    for (auto iter = states.begin(); iter != states.end(); iter++)
    {
        if ((*iter)->contains(state))
        {
            parents.push_back(*iter);
        }
    }

    if (parents.size() == 1)
    {
        result = *parents.begin();
    }
    else if (parents.size() > 1)
    {
        int idx = 0;
        CState** cs_array = new CState*[parents.size() * sizeof(result)];
        for (auto iter = parents.begin(); iter != parents.end(); iter++)
        {
            cs_array[idx] = *iter;
            idx++;
        }
        std::qsort(cs_array, parents.size(), sizeof(cs_array[0]), CState::compare);
        result = cs_array[0];
        delete[] cs_array;
    }

    return result;
}

// Find the initial state
CState* Diagram::starting_state()
{
    CState* result = NULL;

    for (auto iter = states.begin(); iter != states.end(); iter++)
    {
        CState* cs = *iter;
        if (state_parent(*cs) == NULL)
        {
            if (cs->get_default())
            {
                result = find_default_substate(cs);
            }
        }
    }

    if (result == NULL)
    {
        // User hasn't provided a default state
        m_error = true;
    }

    return result;
}

CState* Diagram::find_default_substate(CState* cs)
{
    std::list<CState*> substates;
    int nSubstates;
    CState* result = cs;

    for (auto iter = states.begin(); iter != states.end(); iter++)
    {
        if (cs->contains(**iter))
        {
            substates.push_back(*iter);            
        }
    }

    nSubstates = substates.size();
    if (nSubstates > 1)
    {
        bool found;
        int idx = 0;
        // copy list into array and sort
        CState** cs_array = new CState*[nSubstates * sizeof(CState*)];
        for (auto iter = substates.begin(); iter != substates.end(); iter++)
        {
            cs_array[idx] = *iter;
            idx++;
        }
        std::qsort(cs_array, nSubstates, sizeof(cs_array[0]), CState::compare);

        // cs_array[nSubstates - 1] should be guaranteed to be only contained
        // by 'cs' and not a substate of 'cs'
        found = false;
        for (idx = nSubstates - 1; idx > 0; idx--)
        {
            if (CState::compare(cs_array[idx], cs_array[nSubstates - 1]) == 0)
            {
                if (found == false && cs_array[idx]->get_default())
                {
                    found = true;
                    result = cs_array[idx];
                }
                else if (found == true && cs_array[idx]->get_default())
                {
                    // Two simultaneous default states at the same rank
                    m_error = true;
                }
            }
        }
        delete[] cs_array;

        if (found == true)
        {
            // recursion here...
            result = find_default_substate(result);
        }
        else
        {
            // No default state where one is needed
            m_error = true;
        }
    }
    else if (nSubstates == 1)
    {
        // States normally will not have 1 substate...
        result = *substates.begin();
    }

    return result;
}

const char* Diagram::dependencies() const
{
    const char* result = NULL;

    if (!m_dependencies->empty())
    {
        result = m_dependencies->c_str();
    }

    return result;
}

void Diagram::dependencies(const char* text)
{
    m_dependencies->assign(text);
}

const char* Diagram::internals() const
{
    const char* result = NULL;

    if (!m_internals->empty())
    {
        result = m_internals->c_str();
    }

    return result;
}

void Diagram::internals(const char* text)
{
    m_internals->assign(text);
}

bool Diagram::no_text(const char* text)
{
    bool result = false;

    if (text == NULL)
    {
        result = true;
    }
    else if (0 == std::strcmp(text, "nil"))
    {
        result = true;
    }

    return result;
}

