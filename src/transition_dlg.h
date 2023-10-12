#ifndef TRANSITION_DLG_H
#define TRANSITION_DLG_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Button.H>
#include "ctransition.h"

class TransitionDialog
{
public:
    TransitionDialog(CTransition* ct);
    void show();

private:
    Fl_Double_Window *mainWin;
    Fl_Input *name;
    Fl_Value_Input *priority;
    Fl_Text_Editor *condition;
    Fl_Text_Editor *action;
    Fl_Text_Buffer *condition_buf;
    Fl_Text_Buffer *action_buf;
    CTransition* m_data;

    // callbacks
    static void cb_Cancel(Fl_Button*, void*);
    inline void cb_Cancel_i(Fl_Button*, void*);
    static void cb_OK(Fl_Button*, void*);
    inline void cb_OK_i(Fl_Button*, void*);
};

#endif
