#ifndef DATA_CALLBACK_H
#define DATA_CALLBACK_H

#include "diagram.h"
#include "ctransition.h"
#include "cstate.h"

class DataCallback
{
public:
    DataCallback();
    ~DataCallback();

    Diagram* get_diagram() const;
    Diagram* new_diagram();

    CTransition* create_transition(const char* event,
                                   std::array<int, 4> position,
                                   const char* name = "transition",
                                   int priority = 0);
    void destroy_transition(CTransition* ct);
    CState* create_state(const char* name,
                         std::array<int, 4> position);
    void destroy_state(CState* cs);
};

// The controller will create this for viewer use
extern DataCallback* data_callback;

#endif
