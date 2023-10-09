#include "model.h"

Model* theModel;

Model::Model()
{
    m_diagram = new Diagram;
}

Model::Model(const char* file_name)
{
    
}

Model::~Model()
{
    delete m_diagram;
}

Diagram* Model::diagram() const
{
    return m_diagram;
}

