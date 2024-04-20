#ifndef MYNOTEBOOK_H
#define MYNOTEBOOK_H

#include <gtkmm.h>
#include "MyValue.h"
#include "MyDisplayBuffer.h"

// MyNoteBook is a Gtk::Window that contains a packed Gtk:Notebook,
// which contains different panes that is a re-interpretation of
// the ncurses example.
class MyNoteBook : public Gtk::Window
{
public:
    MyNoteBook();
    virtual ~MyNoteBook();

protected:
    //Signal handlers:
    void on_button_quit();
    void on_notebook_switch_page(Gtk::Widget* page, guint page_num);

    //Child widgets:
    Gtk::Box m_VBox;
    Gtk::Notebook m_Notebook;

    // tab one widgets
    Gtk::Box tab_box_1;
    Gtk::Label m_Label1;

    // tab two widgets and signal handlers
    MyValue        value;

    Gtk::VBox      tab_box_2;
    Gtk::Label     value_label;
    Gtk::ButtonBox value_manipulation_buttons;
    Gtk::Button    incr_button;
    Gtk::Button    decr_button;
    Gtk::Button    reset_button;

    void increment_value();
    void decrement_value();
    void reset_value();

    // tab three widgets and signal handlers
    MyDisplayBuffer        displayBuffer;

    Gtk::VBox              tab_box_3;
    Gtk::Label             display_label;
    std::string            display_string;
    Pango::FontDescription font;
    Gtk::ButtonBox         display_manipulation_buttons;
    Gtk::Button            north_button;
    Gtk::Button            south_button;
    Gtk::Button            east_button;
    Gtk::Button            west_button;

    void move_north();
    void move_south();
    void move_east();
    void move_west();
    void render_display();

    // The quit button widgets
    Gtk::ButtonBox button_box;
    Gtk::Button    button_quit;

private:
    // tab initializers that are only called
    // from the constructor
    void initialize_tab_1();
    void initialize_tab_2();
    void initialize_tab_3();
};

#endif //MYNOTEBOOK_H