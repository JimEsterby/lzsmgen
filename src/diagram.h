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
    CState* find_default_substate(CState* state);
    bool m_error;  // If true, there is an error in the diagram
    std::string* m_dependencies;  // metadata
    std::string* m_internals;  // metadata

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
    CState* state_parent(const CState& state) const;
    CState* starting_state();
    bool problem() const { return m_error; }
    const char* dependencies() const;
    void dependencies(const char* text);
    const char* internals() const;
    void internals(const char* text);
    static bool no_text(const char* text);
};

#endif
