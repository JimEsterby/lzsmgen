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
    std::array<int, 4> position;
    int m_priority;

public:
    CTransition(const char* condition,
                const char* name,
                int x1, int y1, int x2, int y2,
                int priority = 0);
    virtual ~CTransition();
    void action(const char* text);
    const char* action() const;
    void condition(const char* text);
    const char* condition() const;
    void name(const char* text);
    const char* name() const;
    int priority() const { return m_priority; }
    void priority(int value) { m_priority = value; }
    void resize(int x1, int y1, int x2, int y2);
};

#endif
