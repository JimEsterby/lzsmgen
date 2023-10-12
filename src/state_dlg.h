#ifndef STATE_DLG_H
#define STATE_DLG_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include "cstate.h"

class StateDialog
{
public:
    StateDialog(CState* cs);
    void show();

private:
    Fl_Double_Window* mainWin;
    Fl_Input* name;
    Fl_Check_Button* is_default;
    Fl_Text_Editor* entry;  // entry action
    Fl_Text_Editor* during;  // during action
    Fl_Text_Buffer* entry_buf;
    Fl_Text_Buffer* during_buf;
    CState* m_data;

    // callbacks
    static void cb_Cancel(Fl_Button*, void*);
    inline void cb_Cancel_i(Fl_Button*, void*);
    static void cb_OK(Fl_Button*, void*);
    inline void cb_OK_i(Fl_Button*, void*);
};

#endif
