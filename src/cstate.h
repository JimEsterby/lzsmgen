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
    std::array<int, 4> m_position;
    bool isDefault;

public:
    CState(const char* name,
           int x1, int y1, int x2, int y2,
           bool default_state = false);
    virtual ~CState();
    bool is_substate_of(const CState& cs) const;
    bool contains(const CState& cs) const;
    bool contains(int x, int y) const;
    void name(const char* text);
    void during_action(const char* text);
    void entry_action(const char* text);
    const char* during_action() const;
    const char* entry_action() const;
    const char* name() const;
    std::array<int, 4> position() const { return m_position; }
    void resize(int x1, int y1, int x2, int y2);
    void set_default() { isDefault = true; }
    void set_not_default() { isDefault = false; }
    bool get_default() const { return isDefault; }

};

#endif
