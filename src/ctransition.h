#ifndef CTRANSITION_H
#define CTRANSITION_H

#include<string>
#include<array>

class CTransition
{
private:
    std::string* m_name;  // Becomes generated function
    std::string* m_condition;  // Event that triggers transition
    std::string* m_action;  // Action(s) to be taken when transition is triggered
    std::array<int, 4> m_position;
    int m_priority;

public:
    CTransition(const char* condition,
                const char* name,
                int x1, int y1, int x2, int y2,
                int priority = 1);
    virtual ~CTransition();
    void action(const char* text);
    const char* action() const;
    void condition(const char* text);
    const char* condition() const;
    void name(const char* text);
    const char* name() const;
    int priority() const { return m_priority; }
    void priority(int value) { m_priority = value; }
    std::array<int, 4> position() const { return m_position; }
    void resize(int x1, int y1, int x2, int y2);

    static int compare(const CTransition* a, const CTransition* b);
    static void bubble_sort(CTransition* array[], int nElements);

    // comparison operators needed for sorting based on priority with lower
    // values of priority representing higher priorities
    friend bool operator==(const CTransition& a, const CTransition& b)
    {
        return (a.m_priority == b.m_priority);
    }
    friend bool operator!=(const CTransition& a, const CTransition& b)
    {
        return (a.m_priority != b.m_priority);
    }
    friend bool operator<(const CTransition& a, const CTransition& b)
    {
        return (a.m_priority < b.m_priority);
    }
    friend bool operator>(const CTransition& a, const CTransition& b)
    {
        return (a.m_priority > b.m_priority);
    }
    friend bool operator<=(const CTransition& a, const CTransition& b)
    {
        return !(a < b);
    }
    friend bool operator>=(const CTransition& a, const CTransition& b)
    {
        return !(a > b);
    }
};

#endif
