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

struct Comment {
    std::string text;
};

class ButtonWindow : public Gtk::Window {
public:
    ButtonWindow();



private:
    void on_button_clicked(const std::string& dbPath, const std::string& tableName, const std::string& attribute);
    void on_fetch_reviews_clicked();
    void on_add_napspot_clicked();
    void on_button_get_datetime_clicked();
    void on_submit_review();
    void initialize_tab_1();
    void initialize_tab_2();
    void initialize_tab_3();
    void initialize_tab_4();
    void initialize_tab_5();
    void initialize_tab_6();
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
    Gtk::Box tab_box_4;
    Gtk::Box tab_box_5;

    //tab 2
    Gtk::Entry* m_entry_name;
    Gtk::TextView* m_text_view;
    Gtk::ComboBoxText* m_combo_rating;

    //tab 3
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


    //tab4
    Gtk::Entry* m_napspot_name;
    Gtk::ComboBoxText* m_combo_attr1;
    Gtk::ComboBoxText* m_combo_attr2;
    Gtk::ComboBoxText* m_combo_attr3;
    Gtk::TreeView m_treeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    Gtk::Entry* m_entry_napspot_id; // Add the declaration for m_entry_napspot_id
    Gtk::TreeView m_treeView_reviews; // Add the declaration for m_treeView_reviews
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel_reviews; // Add the declaration for m_refTreeModel_reviews

    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumns() {
            add(m_col_id);
            add(m_col_name);
            add(m_col_attributes);
        }

        Gtk::TreeModelColumn<int> m_col_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<Glib::ustring> m_col_attributes;
    };

    ModelColumns m_columns;

    class ModelColumnsReviews : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumnsReviews() {
            add(m_col_review_id);
            add(m_col_user_id);
            add(m_col_text);
            add(m_col_rating);
        }

        Gtk::TreeModelColumn<int> m_col_review_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_user_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_text;
        Gtk::TreeModelColumn<int> m_col_rating;
    };

    ModelColumnsReviews m_columns_reviews; // Add the declaration for m_columns_reviews
};

#endif // BUTTONWINDOW_H