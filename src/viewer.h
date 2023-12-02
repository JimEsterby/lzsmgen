#ifndef viewer_h
#define viewer_h

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Button.H>
#include "diagram_editor.h"

class Viewer
{
public:
    Viewer();
    void show(int argc, char *argv[]);
    int run();

private:
    Fl_Double_Window* topLevel;  // main application window
    Fl_Double_Window* canvas;
    DiagramEditor* editor;
    Fl_Double_Window* palette;
    Fl_Box* palette_box;  // For resizing/layout

    // Layout
    Fl_Group* palette_container;
    Fl_Group* palette_a;
    Fl_Group* palette_gv;  // Vertical group
    Fl_Box* palette_h;
    Fl_Box* palette_v;

    // Palette items
    Fl_Button* add_state;
    Fl_Button* add_transition;

    static Fl_Menu_Item mainMenu[];

    void load_diagram();

    // callbacks
    inline void cb_New_i(Fl_Menu_*, void*);
    inline void cb_Open_i(Fl_Menu_*, void*);
    inline void cb_Save_i(Fl_Menu_*, void*);
    inline void cb_SaveAs_i(Fl_Menu_*, void*);
    inline void cb_Test_i(Fl_Menu_*, void*);
    inline void cb_Exit_i(Fl_Menu_*, void*);
    inline void cb_MetaData_i(Fl_Menu_*, void*);
    inline void cb_Refresh_i(Fl_Menu_*, void*);
    inline void cb_Delete_i(Fl_Menu_*, void*);
    inline void cb_GenCode_i(Fl_Menu_*, void*);
    inline void cb_NewState_i(Fl_Button*, void*);
    inline void cb_NewTransition_i(Fl_Button*, void*);

    static void cb_New(Fl_Menu_*, void*);
    static void cb_Open(Fl_Menu_*, void*);
    static void cb_Save(Fl_Menu_*, void*);
    static void cb_SaveAs(Fl_Menu_*, void*);
    static void cb_Test(Fl_Menu_*, void*);
    static void cb_Exit(Fl_Menu_*, void*);
    static void cb_MetaData(Fl_Menu_*, void*);
    static void cb_Refresh(Fl_Menu_*, void*);
    static void cb_Delete(Fl_Menu_*, void*);
    static void cb_GenCode(Fl_Menu_*, void*);
    static void cb_NewState(Fl_Button*, void*);
    static void cb_NewTransition(Fl_Button*, void*);


    static const int border = 20;
    static const int width = 480;
    static const int height = 280;
    static const int mb_height = 25;  // menu bar height
    static const int palette_width = 160;
};

Viewer* open_viewer(int argc, char* argv[]);

#endif
