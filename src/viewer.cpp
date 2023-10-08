#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tile.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include "viewer.h"
#include "state_pict.h"
#include "transition_pict.h"
#include "file_callback.h"
#include "data_callback.h"

// Main application menu
Fl_Menu_Item Viewer::mainMenu[] =
{
    { "&File", 0,  0, 0, (int)FL_SUBMENU, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "New", 0,  (Fl_Callback*)Viewer::cb_New, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Open...", 0, (Fl_Callback*)Viewer::cb_Open, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Save", 0, 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Save as...", 0, 0, 0, (int)FL_MENU_DIVIDER, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "E&xit", 0, (Fl_Callback*)Viewer::cb_Exit, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    {0,0,0,0,0,0,0,0,0},
    { "&Edit", 0, 0, 0, (int)FL_SUBMENU, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Undo", FL_CTRL+'z', 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Redo", FL_CTRL+'y', 0, 0, (int)FL_MENU_DIVIDER, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Cut", FL_CTRL+'x', 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Copy", FL_CTRL+'c', 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Paste", FL_CTRL+'v', 0, 0, (int)FL_MENU_DIVIDER, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Delete", FL_Delete, (Fl_Callback*)Viewer::cb_Delete, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    {0,0,0,0,0,0,0,0,0},
    { "Build", 0, 0, 0, (int)FL_SUBMENU, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "C-code", 0, 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Image", 0, 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    // Remove later, but useful for concept exploration
    { "Test", 0, (Fl_Callback*)Viewer::cb_Test, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    {0,0,0,0,0,0,0,0,0},
    { "&Help", 0, 0, 0, (int)FL_SUBMENU, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Documentation...", 0, 0, 0, (int)FL_MENU_DIVIDER, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "About...", 0, 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    {0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0}
};

// Callback methods

// Menu command callbacks
void Viewer::cb_New_i(Fl_Menu_*, void*)
{
    fl_alert("New command");
}

void Viewer::cb_Test_i(Fl_Menu_*, void*)
{
    fl_alert("Editor children = %d", editor->children());
    for (int i = 0; i < editor->children(); i++)
    {
        editor->child(i)->damage(FL_DAMAGE_CHILD);
    }
    editor->redraw();
}

void Viewer::cb_Exit_i(Fl_Menu_*, void*)
{
    this->topLevel->hide();
}

void Viewer::cb_Delete_i(Fl_Menu_*, void*)
{
    ComponentPict* cp = editor->selected_component();

    if (cp)
    {
        cp->unselect();
        editor->select_component(NULL);
        cp->hide();
        editor->remove(cp);
        delete cp;
    }
}

// Other control callbacks
void Viewer::cb_NewState_i(Fl_Button* btn, void* data)
{
    StatePict* sp = new StatePict(10, 10, 75, 45);

    editor->add((Fl_Widget*) sp);
    editor->redraw();
}

void Viewer::cb_NewTransition_i(Fl_Button*, void*)
{
    TransitionPict* tp = new TransitionPict(10, 60, 75, 45);
    editor->add((Fl_Widget*) tp);
    editor->redraw();
}


// Callback "helpers"

// Menu command callback helpers
void Viewer::cb_New(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_New_i(menu, data);
}

void Viewer::cb_Open(Fl_Menu_* menu, void* data)
{
    char* file_name;
    //Viewer* v = (Viewer*)menu->parent()->user_data();

    file_name = fl_file_chooser("Open diagram file", "Diagram (*.json", NULL);

    if (file_name)
    {
        if (file_callback->open_file_request(file_name))
        {
            // TODO
            fl_alert("Opened file %s", file_name);
        }
    }
}

void Viewer::cb_Test(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Test_i(menu, data);
}

void Viewer::cb_Exit(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Exit_i(menu, data);
}

void Viewer::cb_Delete(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Delete_i(menu, data);
}

// Other control command callback helpers
void Viewer::cb_NewState(Fl_Button* btn, void* data)
{
    ((Viewer*)data)->cb_NewState_i(btn, data);
}

void Viewer::cb_NewTransition(Fl_Button* btn, void* data)
{
    ((Viewer*)data)->cb_NewTransition_i(btn, data);
}

// Constructor, creates the main window and controls and performs layout
Viewer::Viewer()
{
    topLevel = new Fl_Double_Window(width, height, "State Machine Generator");
    topLevel->user_data((void*)(this));
    topLevel->resizable(topLevel);
    {
        Fl_Menu_Bar* mb = new Fl_Menu_Bar(0, 0, width, mb_height);
        mb->box(FL_NO_BOX);
        mb->menu(mainMenu);

        // Palette and canvas editing area are tiled side-by-side
        Fl_Tile* tile = new Fl_Tile(0, mb_height, width, height - mb_height);
        {
            Fl_Box* r = new Fl_Box(tile->x() + border,
                                   tile->y() + border,
                                   tile->w() - 2 * border,
                                   tile->h() - 2 * border);
            tile->resizable(r);

            // palette window
            palette = new Fl_Double_Window(0,
                                           mb_height,
                                           palette_width,
                                           height - mb_height);
            // Draw boundaries around the palette
            palette->box(FL_NO_BOX);
            {
                palette_box = new Fl_Box(0, 0, palette_width, height - mb_height);
                palette_box->box(FL_DOWN_BOX);
                palette_box->color(9);
                palette_box->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
            }
            palette->resizable(palette_box);

            // layout control of palette
            palette_a = new Fl_Group(0, 0, palette_width, height - mb_height);
            {
                palette_gv = new Fl_Group(0, 0, palette_a->w(), palette_a->h() - 10);
                {
                    palette_container = new Fl_Group(0, 0, palette_a->w() - 10, palette_a->h() - 10);
                    {
                        add_state = new Fl_Button(20, 20, 75, 45, "State");
                        //add_state->box(FL_ROUNDED_BOX);
                        add_state->color((Fl_Color)215);  // light yellow
                        add_state->callback((Fl_Callback*)cb_NewState);
                        add_state->user_data((void*)this);
                        add_transition = new Fl_Button(20, 85, 75, 25, "Transition");
                        add_transition->callback((Fl_Callback*)cb_NewTransition);
                        add_transition->user_data((void*)this);
                    }
                    palette_container->end();

                    palette_v = new Fl_Box(palette_container->w(), 0, 10, palette_container->h());
                }
                palette_gv->resizable(palette_v);
                palette_gv->end();

                palette_h = new Fl_Box(0, palette_gv->h(), palette_gv->w(), 10);
                
            }
            palette_a->resizable(palette_h);
            palette_a->end();

            //add_state = new Fl_Button(20, 20, 75, 25, "State");
            //add_transition = new Fl_Button(20, 65, 75, 25, "Transition");

            palette->end();

            // canvas editing area
            canvas = new Fl_Double_Window(palette_width,
                                          mb_height,
                                          width - palette_width,
                                          height - mb_height);

            // Draw boundaries around canvas editing area
            canvas->box(FL_NO_BOX);
            {
                editor = new DiagramEditor(0, 0, width - palette_width, height - mb_height, "Text");
                editor->box(FL_DOWN_BOX);
                editor->align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE|FL_ALIGN_WRAP);
                editor->end();
            }
            canvas->resizable(editor);
            canvas->end();
        }
        tile->end();
        topLevel->resizable(tile);
   }
    
    topLevel->end();
}

// Open the window on the display
void Viewer::show(int argc, char *argv[])
{
    topLevel->show(argc, argv);
}

// Start the GUI message pump
int Viewer::run()
{
    return Fl::run();
}

// Load diagram into the canvas area 
void Viewer::load_diagram()
{

}

// GUI initialization function to be called by the controller
Viewer* open_viewer(int argc, char* argv[])
{
    Viewer* retval = new Viewer;

    Fl::visual(FL_DOUBLE | FL_INDEX);
    retval->show(argc, argv);

    return retval;
}
