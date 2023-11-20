#ifndef META_DLG_H
#define META_DLG_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Button.H>
#include "diagram.h"

class MetaDataDialog
{
public:
    MetaDataDialog(Diagram* dgm);
    void show();
    bool OK_pressed() const { return m_OK_pressed; }

private:
    Fl_Double_Window* mainWin;
    Fl_Text_Editor* dependency;  // Dependencies
    Fl_Text_Editor* internal;  // Internal symbols
    Fl_Text_Buffer* dependency_buf;
    Fl_Text_Buffer* internal_buf;
    Diagram* m_data;
    bool m_OK_pressed;

    // callbacks
    static void cb_Cancel(Fl_Button*, void*);
    inline void cb_Cancel_i(Fl_Button*, void*);
    static void cb_OK(Fl_Button*, void*);
    inline void cb_OK_i(Fl_Button*, void*);
};

#endif
