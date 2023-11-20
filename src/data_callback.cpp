#include "data_callback.h"
#include "model.h"

DataCallback* data_callback;  // THE data callback object

DataCallback::DataCallback()
{

}

DataCallback::~DataCallback()
{

}

Diagram* DataCallback::get_diagram() const
{
    return theModel->diagram();
}

Diagram* DataCallback::new_diagram()
{
    return theModel->new_diagram();
}

CTransition* DataCallback::create_transition(const char* event,
                                             std::array<int, 4> position,
                                             const char* name,
                                             int priority)
{
    CTransition* t = new CTransition(event,
                                     name,
                                     position[0],
                                     position[1],
                                     position[2],
                                     position[3],
                                     priority);

    // Add transition to the diagram
    theModel->diagram()->add_transition(t);

    return t;
    
}

void DataCallback::destroy_transition(CTransition* ct)
{
    theModel->diagram()->remove_transition(ct);
}

CState* DataCallback::create_state(const char* name,
                                   std::array<int, 4>position)
{
    CState* cs = new CState(name,
                            position[0],
                            position[1],
                            position[2],
                            position[3]);

    // Add state to diagram
    theModel->diagram()->add_state(cs);
    
    return cs;
}

void DataCallback::destroy_state(CState* cs)
{
    theModel->diagram()->remove_state(cs);
}

