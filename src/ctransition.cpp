#include "ctransition.h"

CTransition::CTransition(const char* condition,
                         const char* name,
                         int x1, int y1, int x2, int y2,
                         int priority)
{
    m_name = new std::string(name);
    m_condition = new std::string(condition);
    m_action = new std::string();  // empty string
    m_position[0] = x1;
    m_position[1] = y1;
    m_position[2] = x2;
    m_position[3] = y2;
    m_priority = priority;
}

CTransition::~CTransition()
{
    delete m_name;
    delete m_condition;
    delete m_action;
}

void CTransition::action(const char* text)
{
    m_action->assign(text);
}

const char* CTransition::action() const
{
    const char* result = NULL;

    if (!m_action->empty())
    {
        result = m_action->c_str();
    }

    return result;
}

void CTransition::condition(const char* text)
{
    m_condition->assign(text);
}

const char* CTransition::condition() const
{
    const char* result = NULL;

    if (!m_condition->empty())
    {
        result = m_condition->c_str();
    }

    return result;
}

void CTransition::name(const char* text)
{
    m_name->assign(text);
}

const char* CTransition::name() const
{
    const char* result = NULL;

    if (!m_name->empty())
    {
        result = m_name->c_str();
    }

    return result;
}

void CTransition::resize(int x1, int y1, int x2, int y2)
{
    m_position[0] = x1;
    m_position[1] = y1;
    m_position[2] = x2;
    m_position[3] = y2;
}

void CTransition::bubble_sort(CTransition* array[], int nElements)
{
    int idx1;
    int idx2;

    for (idx1 = 0; idx1 < nElements; idx1++)
    {
        for (idx2 = 0; idx2 < nElements - idx1 - 1; idx2++)
        {
            if (1 == CTransition::compare(array[idx2], array[idx2 + 1]))
            {
                // Swap elements
                CTransition* temp = array[idx2];
                array[idx2] = array[idx2 + 1];
                array[idx2 + 1] = temp;
            }
        }
    }
}

/*
   Intended for use in std::qsort. Ordinarily, I would prefer using a sort
   method in a STL container, but CppUTest is flagging memory allocation errors
   for STL stuff.

   Returns -1 if a->priority is less than b->priority
            0 if a->priority equals b->priority
            1 if a->priority is greater thn b->priority
*/
int CTransition::compare(const CTransition* a, const CTransition* b)
{
    int result;

    if (a->priority() < b->priority())
    {
        result = -1;
    }
    else if (a->priority() > b->priority())
    {
        result = 1;
    }
    else
    {
        result = 0;
    }

    return result;
}
