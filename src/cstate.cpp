#include "cstate.h"

CState::CState(const char* name,
               int x1, int y1, int x2, int y2,
               bool default_state)
{
    m_name = new std::string(name);
    m_during_action = new std::string();  // empty string
    m_entry_action = new std::string();  // empty string
    m_position[0] = x1;
    m_position[1] = y1;
    m_position[2] = x2;
    m_position[3] = y2;
    isDefault = default_state;
}

CState::~CState()
{
    delete m_name;
    delete m_during_action;
    delete m_entry_action;
}

bool CState::is_substate_of(const CState* cs) const
{
    bool result = false;

    if (m_position[0] > cs->position()[0] &&
        m_position[1] > cs->position()[1] &&
        m_position[2] < cs->position()[2] &&
        m_position[3] < cs->position()[3])
    {
        result = true;
    }

    return result;
}

bool CState::contains(const CState* cs) const
{
    bool result = false;

    if (m_position[0] < cs->position()[0] &&
        m_position[1] < cs->position()[1] &&
        m_position[2] > cs->position()[2] &&
        m_position[3] > cs->position()[3])
    {
        result = true;
    }

    return result;
}

bool CState::contains(int x, int y) const
{
    bool result = false;

    if (x >= m_position[0] && x <= m_position[2] &&
        y >= m_position[1] && y <= m_position[3])
    {
        result = true;
    }

    return result;
}

void CState::name(const char* text)
{
    m_name->assign(text);
}

void CState::during_action(const char* text)
{
    m_during_action->assign(text);
}

void CState::entry_action(const char* text)
{
    m_entry_action->assign(text);
}

const char* CState::name() const
{
    const char* result = NULL;

    if (!m_name->empty())
    {
        result = m_name->c_str();
    }

    return result;
}

const char* CState::during_action() const
{
    const char* result = NULL;

    if (!m_during_action->empty())
    {
        result = m_during_action->c_str();
    }

    return result;
}

const char* CState::entry_action() const
{
    const char* result = NULL;

    if (!m_entry_action->empty())
    {
        result = m_entry_action->c_str();
    }

    return result;
}

void CState::resize(int x1, int y1, int x2, int y2)
{
    m_position[0] = x1;
    m_position[1] = y1;
    m_position[2] = x2;
    m_position[3] = y2;
}

