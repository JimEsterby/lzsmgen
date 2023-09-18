#include "data_callback.h"

DataCallback* data_callback;  // THE data callback object

DataCallback::DataCallback()
{

}

DataCallback::~DataCallback()
{

}

Diagram* DataCallback::get_diagram() const
{
    return nullptr;
}
