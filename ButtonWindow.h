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
    void initialize_tab_4();
    void initUI();
    void on_post_comment_button_clicked();
    void on_comment_button_clicked(std::string post_text);
    void update_forum_text_view();
    void add_post_with_comment_button(const std::string& post_text);


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

    //declare variable for tab4
    Gtk::TextView forum_text_view;
    Gtk::Entry forum_text_entry;
    Gtk::Button post_comment_button;
    Gtk::Box posts_container; // Use Gtk::Box instead of Gtk::VBox
    std::vector<std::pair<std::string, std::vector<Comment>>> forum_posts;
    std::vector<std::pair<Gtk::Button*, std::string>> comment_buttons; // Pair of buttons and the post text they correspond to




};

#endif // BUTTONWINDOW_H