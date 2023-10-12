#ifndef CSTATE_H
#define CSTATE_H

#include<string>
#include<array>

class CState
{
private:
    std::string* m_name;
    std::string* m_entry_action;
    std::string* m_during_action;
    std::array<int, 4> position;
    bool isDefault;

public:
    CState(const char* name,
           int x1, int y1, int x2, int y2,
           bool default_state = false);
    virtual ~CState();
    void name(const char* text);
    void during_action(const char* text);
    void entry_action(const char* text);
    const char* during_action() const;
    const char* entry_action() const;
    const char* name() const;
    void resize(int x1, int y1, int x2, int y2);
    void set_default() { isDefault = true; }
    void set_not_default() { isDefault = false; }
    bool get_default() const { return isDefault; }

};

#endif
