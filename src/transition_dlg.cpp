#include <FL/Fl_Group.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include "transition_dlg.h"
#include <FL/Fl_ask.H>


TransitionDialog::TransitionDialog(CTransition* ct)
{
    m_data = ct;

    mainWin = new Fl_Double_Window(331, 337, "Transition Properties");
    mainWin->user_data((void*)(this));
    {
        name = new Fl_Input(80, 15, 120, 25, "Name:");
        if (ct->name())
        {
            name->value(ct->name());
        }

        priority = new Fl_Value_Input(80, 56, 35, 24, "Priority:");
        priority->maximum(40);
        priority->step(1);
        priority->value(ct->priority());
        
        condition = new Fl_Text_Editor(80, 95, 220, 75, "Condition:");
        condition_buf = new Fl_Text_Buffer;
        condition->buffer(condition_buf);
        condition->align(Fl_Align(FL_ALIGN_LEFT_TOP));
        condition_buf->text(ct->condition());

        action = new Fl_Text_Editor(80, 190, 220, 95, "Transition\nAction:");
        action_buf = new Fl_Text_Buffer;
        action->buffer(action_buf);
        action->align(Fl_Align(FL_ALIGN_LEFT_TOP));
        action_buf->text(ct->action());
        
        Fl_Group::current()->resizable(action);
        
        Fl_Group* g_btn = new Fl_Group(30, 294, 270, 36);
        {
            // The box is for resizing layout purposes
            Fl_Box* o = new Fl_Box(45, 294, 80, 36);
            Fl_Group::current()->resizable(o);
            
            Fl_Button* btn_cancel = new Fl_Button(145, 300, 70, 25, "Cancel");
            btn_cancel->color((Fl_Color)91);
            btn_cancel->user_data((void*)this);
            btn_cancel->callback((Fl_Callback*)TransitionDialog::cb_Cancel);
            
            Fl_Button* btn_okay = new Fl_Button(230, 300, 70, 25, "OK");
            btn_okay->user_data((void*)this);
            btn_okay->color((Fl_Color)79);
            btn_okay->callback((Fl_Callback*)TransitionDialog::cb_OK);
        }
        g_btn->end();
    }
    mainWin->set_modal();
    mainWin->end();
}

void TransitionDialog::show()
{
	mainWin->show();

    while (mainWin->shown())
    {
        Fl::wait();
    }
}

void TransitionDialog::cb_Cancel_i(Fl_Button* btn, void* data)
{
	mainWin->hide();
}

void TransitionDialog::cb_Cancel(Fl_Button* btn, void* data)
{
	((TransitionDialog*)data)->cb_Cancel_i(btn, data);
}

void TransitionDialog::cb_OK_i(Fl_Button* btn, void* data)
{
    m_data->action(action_buf->text());
    m_data->condition(condition_buf->text());
    m_data->name(name->value());
    m_data->priority(priority->value());

    mainWin->hide();
}

void TransitionDialog::cb_OK(Fl_Button* btn, void* data)
{
    ((TransitionDialog*)data)->cb_OK_i(btn, data);
}
