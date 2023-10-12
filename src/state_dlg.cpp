#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include "state_dlg.h"

StateDialog::StateDialog(CState* cs)
{
    m_data = cs;

    mainWin = new Fl_Double_Window(331, 337, "State Properties");
    mainWin->user_data((void*)(this));
    {
        Fl_Group* top = new Fl_Group(20, 20, 269, 25);
        {
            name = new Fl_Input(80, 20, 120, 25, "Name:");
            name->labelsize(12);
            name->textsize(12);
            if (cs->name())
            {
                name->value(cs->name());
            }
            Fl_Group::current()->resizable(name);
            is_default = new Fl_Check_Button(225, 22, 64, 20, "Default");
            is_default->down_box(FL_DOWN_BOX);
            is_default->labelsize(12);
            if (cs->get_default())
            {
                is_default->set();
            }
        }
        top->end();

        entry = new Fl_Text_Editor(80, 65, 220, 105, "Entry\nAction:");
        entry_buf = new Fl_Text_Buffer;
        entry->buffer(entry_buf);
        entry->labelsize(12);
        entry->textsize(12);
        entry->textfont(FL_COURIER);
        entry->align(Fl_Align(FL_ALIGN_LEFT_TOP));
        entry_buf->text(cs->entry_action());

        during = new Fl_Text_Editor(80, 190, 220, 95, "During\nAction:");
        during_buf = new Fl_Text_Buffer;
        during->buffer(during_buf);
        during->labelsize(12);
        during->textsize(12);
        during->textfont(FL_COURIER);
        during->align(Fl_Align(FL_ALIGN_LEFT_TOP));
        during_buf->text(cs->during_action());
        Fl_Group::current()->resizable(during);

        Fl_Group* bottom = new Fl_Group(30, 294, 270, 36);
        {
            Fl_Box* o = new Fl_Box(45, 294, 80, 36);
            Fl_Group::current()->resizable(o);

            Fl_Button* cancel = new Fl_Button(145, 300, 70, 25, "Cancel");
            cancel->color((Fl_Color)91);
            cancel->user_data((void*)this);
            cancel->callback((Fl_Callback*)StateDialog::cb_Cancel);
            cancel->labelsize(12);

            Fl_Button* okay = new Fl_Button(230, 300, 70, 25, "OK");
            okay->color((Fl_Color)79);
            okay->user_data((void*)this);
            okay->callback((Fl_Callback*)StateDialog::cb_OK);
            okay->labelsize(12);
        }
        bottom->end();
    }
    mainWin->set_modal();
    mainWin->end();
}

void StateDialog::show()
{
    mainWin->show();

    while (mainWin->shown())
    {
        Fl::wait();
    }
}

void StateDialog::cb_Cancel(Fl_Button* btn, void* data)
{
    ((StateDialog*)data)->cb_Cancel_i(btn, data);
}

void StateDialog::cb_Cancel_i(Fl_Button* btn, void* data)
{
    mainWin->hide();
}

void StateDialog::cb_OK(Fl_Button* btn, void* data)
{
    ((StateDialog*)data)->cb_OK_i(btn, data);
}

void StateDialog::cb_OK_i(Fl_Button* btn, void* data)
{
    m_data->name(name->value());
    m_data->entry_action(entry_buf->text());
    m_data->during_action(during_buf->text());

    if (is_default->value())
    {
        m_data->set_default();
    }
    else
    {
        m_data->set_not_default();
    }

    mainWin->hide();
}

