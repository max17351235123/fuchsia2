#ifndef BUTTONWINDOW_H
#define BUTTONWINDOW_H

#include <gtkmm.h>
#include <gtkmm/notebook.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/button.h>

class ButtonWindow : public Gtk::Window {
public:
    ButtonWindow();


private:
    void on_button_clicked(const std::string& dbPath, const std::string& tableName, const std::string& attribute);
    void on_button_get_datetime_clicked();
    void on_submit_review();
    void initialize_tab_1();
    void initialize_tab_2();
    void initialize_tab_3();

    Gtk::Notebook m_Notebook;
    Gtk::Box m_VBox;
    Gtk::Label m_Label1;
    Gtk::Box tab_box_1;
    Gtk::Box tab_box_2;
    Gtk::Box tab_box_3;

    // Declare member variables for tab2 widgets
    Gtk::Entry* m_entry_name;
    Gtk::TextView* m_text_view;
    Gtk::ComboBoxText* m_combo_rating;

    // Declare member variables for tab3 widgets
    Gtk::ComboBoxText* combo_month;
    Gtk::ComboBoxText* combo_year;
    Gtk::ComboBoxText* combo_day_first;
    Gtk::ComboBoxText* combo_day_second;
    Gtk::ComboBoxText* combo_time;
    Gtk::ComboBoxText* combo_am_pm;



};

#endif // BUTTONWINDOW_H