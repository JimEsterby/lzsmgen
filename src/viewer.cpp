#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tile.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include "viewer.h"
#include "state_pict.h"
#include "transition_pict.h"
#include "metadata_dlg.h"
#include "file_callback.h"
#include "data_callback.h"

// Main application menu
Fl_Menu_Item Viewer::mainMenu[] =
{
    { "&File", 0,  0, 0, (int)FL_SUBMENU, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "New", 0,  (Fl_Callback*)Viewer::cb_New, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Open...", 0, (Fl_Callback*)Viewer::cb_Open, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Save", FL_CTRL+'s', (Fl_Callback*)Viewer::cb_Save, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Save as...", FL_CTRL+'S', (Fl_Callback*)Viewer::cb_SaveAs, 0, (int)FL_MENU_DIVIDER, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "E&xit", 0, (Fl_Callback*)Viewer::cb_Exit, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    {0,0,0,0,0,0,0,0,0},
    { "&Edit", 0, 0, 0, (int)FL_SUBMENU, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
#if 0  // TODO: Add later
    { "Undo", FL_CTRL+'z', 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Redo", FL_CTRL+'y', 0, 0, (int)FL_MENU_DIVIDER, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Cut", FL_CTRL+'x', 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Copy", FL_CTRL+'c', 0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Paste", FL_CTRL+'v', 0, 0, (int)FL_MENU_DIVIDER, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
#endif
    { "Refresh", 0, (Fl_Callback*)Viewer::cb_Refresh, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Metadata...", 0, (Fl_Callback*)Viewer::cb_MetaData, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "Delete", FL_Delete, (Fl_Callback*)Viewer::cb_Delete, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    {0,0,0,0,0,0,0,0,0},
    { "Build", 0, 0, 0, (int)FL_SUBMENU, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
    { "C-code", 0, (Fl_Callback*)Viewer::cb_GenCode, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 12, 0 },
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
void Viewer::cb_New_i(Fl_Menu_* menu, void* data)
{
    if (editor->changed())
    {
        // Allow user to cancel
        if (fl_choice("Lose unsaved changes?",
                      "Cancel", "Lose Changes", NULL) == 0)
        {
            return;
        }         
    }

    editor->clear_selections();
    editor->clear();
    editor->reset_changed();
    editor->redraw();

    (void)data_callback->new_diagram();  // Must be last!
}

void Viewer::cb_Open_i(Fl_Menu_* menu, void* data)
{
    char* file_name;

    if (editor->changed())
    {
        // Allow user to cancel
        if (fl_choice("Lose unsaved changes?",
                      "Cancel", "Lose Changes", NULL) == 0)
        {
            return;
        }         
    }

    file_name = fl_file_chooser("Open diagram file", "Diagram (*.json", NULL);

    if (file_name)
    {
        editor->clear_selections();
        editor->clear();

        if (file_callback->open(file_name))
        {
            std::list<CState*> state;
            std::list<CTransition*> transition;
            Diagram* d = data_callback->get_diagram();
            state = d->state_list();
            transition = d->transition_list();

            for (auto iter = state.begin(); iter != state.end(); iter++)
            {
                StatePict* sp = new StatePict(*iter);
                editor->add((Fl_Widget*) sp);
            }

            for (auto iter = transition.begin(); iter != transition.end(); iter++)
            {
                TransitionPict* tp = new TransitionPict(*iter);
                editor->add((Fl_Widget*) tp);
            }

            editor->redraw();
            editor->reset_changed();
        }
        else
        {
            fl_alert("Problem reading or opening file:\n%s", file_name);
        }
    }

}

void Viewer::cb_Save_i(Fl_Menu_* menu, void* data)
{
    if (file_callback->loaded())
    {
        if (file_callback->save() == true)
        {
            // No unsaved changes
            editor->reset_changed();
            fl_alert("Saved %s.", file_callback->name());
        }
        else
        {
            fl_alert("Failed to save %s.", file_callback->name());
        }
    }
    else
    {
        cb_SaveAs_i(menu, data);
    }
}

void Viewer::cb_SaveAs_i(Fl_Menu_*, void*)
{
    char* file_name;

    file_name = fl_file_chooser("Save diagram file as", "Diagram (*.json", NULL);

    if (file_name)
    {
        if (file_callback->check_preexisting(file_name))
        {
            // Allow user to cancel
            if (fl_choice("The file, %s, already exists.\nReplace?",
                          "Cancel", "Replace", NULL, file_name) == 0)
            {
                return;
            }
        }

        if (file_callback->save(file_name) == false)
        {
            fl_alert("Failed to save %s.", file_name);
        }
        else  // Save was successful
        {
            // No unsaved changes
            editor->reset_changed();
        }
    }
}

void Viewer::cb_Test_i(Fl_Menu_*, void*)
{
    int states = data_callback->get_diagram()->state_count();
    int transitions = data_callback->get_diagram()->transition_count();
    /*
    fl_alert("Editor children = %d", editor->children());
    for (int i = 0; i < editor->children(); i++)
    {
        editor->child(i)->damage(FL_DAMAGE_CHILD);
    }
    editor->redraw();*/

    fl_alert("We have %d pictures and\n%d objects.", editor->children() - 2, states + transitions);
    editor->redraw();
}

void Viewer::cb_Exit_i(Fl_Menu_* menu, void* data)
{
    if (editor->changed())
    {
        int user_choice = fl_choice("Lose unsaved changes?",
                                    "Cancel",
                                    "Lose Changes",  // default
                                    "Save File");
        if (user_choice == 2)  // Save File
        {
            cb_Save_i(menu, data);
            return;
        }
        else if (user_choice == 0)  // Cancel
        {
            return;
        }        
    }

    this->topLevel->hide();
}

void Viewer::cb_MetaData_i(Fl_Menu_*, void*)
{ 
    MetaDataDialog* d = new MetaDataDialog(data_callback->get_diagram());
    d->show();
    if (d->OK_pressed())
    {
        editor->set_changed();
    }

    delete d;
}

void Viewer::cb_Refresh_i(Fl_Menu_*, void*)
{
    editor->redraw();
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
        editor->set_changed();
    }
}

void Viewer::cb_GenCode_i(Fl_Menu_*, void*)
{
    if (file_callback->generate_code("c"))
    {
        fl_alert("Generated %s.c and %s.h.",
                 file_callback->module(),
                 file_callback->module());
    }
    else
    {
        fl_alert("Code generation failed.");
    }
}

// Other control callbacks
void Viewer::cb_NewState_i(Fl_Button* btn, void* data)
{
    StatePict* sp = new StatePict(10, 10, 75, 45);

    editor->add((Fl_Widget*) sp);
    editor->redraw();
    editor->set_changed();
}

void Viewer::cb_NewTransition_i(Fl_Button*, void*)
{
    TransitionPict* tp = new TransitionPict(10, 60, 75, 45);
    editor->add((Fl_Widget*) tp);
    editor->redraw();
    editor->set_changed();
}


// Callback "helpers"

// Menu command callback helpers
void Viewer::cb_New(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_New_i(menu, data);
}

void Viewer::cb_Open(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Open_i(menu, data);
}

void Viewer::cb_Save(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Save_i(menu, data);
}

void Viewer::cb_SaveAs(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_SaveAs_i(menu, data);
}

void Viewer::cb_Test(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Test_i(menu, data);
}

void Viewer::cb_Exit(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Exit_i(menu, data);
}

void Viewer::cb_MetaData(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_MetaData_i(menu, data);
}

void Viewer::cb_Refresh(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Refresh_i(menu, data);
}

void Viewer::cb_Delete(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_Delete_i(menu, data);
}

void Viewer::cb_GenCode(Fl_Menu_* menu, void* data)
{
    ((Viewer*)(menu->parent()->user_data()))->cb_GenCode_i(menu, data);
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
#if 0
    std::list<CState*> state;
    std::list<CTransition*> transition;
    Diagram* d = data_callback->get_diagram();
    state = d->state_list();
    transition = d->transition_list();

    for (auto iter = state.begin(); iter != state.end(); iter++)
    {
        StatePict* sp = new StatePict(*iter);
        editor->add((Fl_Widget*) sp);
    }

    for (auto iter = transition.begin(); iter != transition.end(); iter++)
    {
        TransitionPict* tp = new TransitionPict(*iter);
        editor->add((Fl_Widget*) tp);
    }

    editor->redraw()
#endif
}

// GUI initialization function to be called by the controller
Viewer* open_viewer(int argc, char* argv[])
{
    Viewer* retval = new Viewer;

    Fl::visual(FL_DOUBLE | FL_INDEX);
    retval->show(argc, argv);

    return retval;
}
