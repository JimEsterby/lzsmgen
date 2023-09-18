#ifndef DATA_CALLBACK_H
#define DATA_CALLBACK_H

#include "diagram.h"

class DataCallback
{
public:
    DataCallback();
    ~DataCallback();

    Diagram* get_diagram() const;
};

// The controller will create this for viewer use
extern DataCallback* data_callback;

#endif
