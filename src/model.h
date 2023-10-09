#ifndef MODEL_H
#define MODEL_H

#include "diagram.h"

class Model
{
public:
    Model();
    Model(const char* file_name);
    ~Model();
    Diagram* diagram() const;

private:
    Diagram* m_diagram;
};

extern Model* theModel;

#endif
