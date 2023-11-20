#include <FL/Fl_Box.H>
#include <FL/Fl_Group.H>
#include "metadata_dlg.h"

MetaDataDialog::MetaDataDialog(Diagram* dgm)
{
    m_data = dgm;
    m_OK_pressed = false;

    mainWin = new Fl_Double_Window(331, 292, "Diagram Metadata");
    mainWin->user_data((void*)(this));
    {
        dependency = new Fl_Text_Editor(100, 20, 200, 105, "Dependencies:");
        dependency_buf = new Fl_Text_Buffer;
        dependency->buffer(dependency_buf);
        dependency->labelsize(12);
        dependency->textsize(12);
        dependency->textfont(FL_COURIER);
        dependency->align(Fl_Align(FL_ALIGN_LEFT_TOP));
        dependency_buf->text(dgm->dependencies());

        internal = new Fl_Text_Editor(100, 145, 200, 95, "Internals:");
        internal_buf = new Fl_Text_Buffer;
        internal->buffer(internal_buf);
        internal->labelsize(12);
        internal->textsize(12);
        internal->textfont(FL_COURIER);
        internal->align(Fl_Align(FL_ALIGN_LEFT_TOP));
        internal_buf->text(dgm->internals());
        Fl_Group::current()->resizable(internal);

        Fl_Group* bottom = new Fl_Group(30, 249, 270, 36);
        {
            Fl_Box* o = new Fl_Box(45, 249, 80, 36);
            Fl_Group::current()->resizable(o);

            Fl_Button* cancel = new Fl_Button(145, 255, 70, 25, "Cancel");
            cancel->color((Fl_Color)91);
            cancel->user_data((void*)this);
            cancel->callback((Fl_Callback*)MetaDataDialog::cb_Cancel);
            cancel->labelsize(12);

            Fl_Button* okay = new Fl_Button(230, 255, 70, 25, "OK");
            okay->color((Fl_Color)79);
            okay->user_data((void*)this);
            okay->callback((Fl_Callback*)MetaDataDialog::cb_OK);
            okay->labelsize(12);
        }
        bottom->end();
    }
    mainWin->set_modal();
    mainWin->end();
}

void MetaDataDialog::show()
{
    mainWin->show();

    while (mainWin->shown())
    {
        Fl::wait();
    }
}

void MetaDataDialog::cb_Cancel(Fl_Button* btn, void* data)
{
    ((MetaDataDialog*)data)->cb_Cancel_i(btn, data);
}

void MetaDataDialog::cb_Cancel_i(Fl_Button* btn, void* data)
{
    mainWin->hide();
}

void MetaDataDialog::cb_OK(Fl_Button* btn, void* data)
{
    ((MetaDataDialog*)data)->cb_OK_i(btn, data);
}

void MetaDataDialog::cb_OK_i(Fl_Button* btn, void* data)
{
    m_OK_pressed = true;
    m_data->dependencies(dependency_buf->text());
    m_data->internals(internal_buf->text());

    mainWin->hide();
}

