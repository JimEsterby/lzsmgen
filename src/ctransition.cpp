#include "ctransition.h"

CTransition::CTransition(const char* condition,
                         const char* name,
                         int x1, int y1, int x2, int y2,
                         int priority)
{
    m_name = new std::string(name);
    m_condition = new std::string(condition);
    m_action = new std::string();  // empty string
    position[0] = x1;
    position[1] = y1;
    position[2] = x2;
    position[3] = y2;
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
    position[0] = x1;
    position[1] = y1;
    position[2] = x2;
    position[3] = y2;
}
