#ifndef CTRANSITION_H
#define CTRANSITION_H

#include<string>
#include<array>

class CTransition
{
private:
    std::string* m_name;  // Maybe not important...
    std::string* m_condition;
    std::string* m_action;
    std::array<int, 4> position;
    int m_priority;

public:
    CTransition(const char* name,
                int x1, int y1, int x2, int y2,
                int priority = 0);
    virtual ~CTransition();
    void action(const char* text);
    const char* action() const;
    void condition(const char* text);
    const char* condition() const;
    void resize(int x1, int y1, int x2, int y2);
};

#endif
