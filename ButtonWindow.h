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

using namespace std;

class ButtonWindow : public Gtk::Window {
public:
    ButtonWindow();

private:

    /**
     * opens a window based on the attribute you clicked
     *
     * @param dbPath path to database
     * @param tableName name of table
     * @param attribute attribute that was clicked
     */
    void on_button_clicked(const std::string& dbPath, const std::string& tableName, const std::string& attribute);

    /**
     * fetches reviews
     */
    void on_fetch_reviews_clicked();

    /**
     * fetches reservations
     */
    void on_fetch_reservations_clicked();
    /**
     * adds a napspot
     */
    void on_add_napspot_clicked();
    /**
     * adds a comment
     */
    void on_post_comment_button_clicked();
    /**
     * adds a comment on a post
     * @param post_text the text of the comment
     */
    void on_comment_button_clicked(string post_text);

    /**
     * updates the forum text
     */
    void update_forum_text_view();
    /**
     * creates a post based on comment text
     * @param post_text the text of the comment
     */
    void add_post_with_comment_button(const string& post_text);
    /**
     * adds a review to the database
     */
    void on_submit_review();

    /**
     * initializes attribute tab
     */
    void initialize_tab_1();
    /**
     * initializes write a review tab
     */
    void initialize_tab_2();
    /**
     * initializes add napspot tab
     */
    void initialize_tab_4();
    /**
     * initializes reviews tab
     */
    void initialize_tab_5();
    /**
     * initializes reservation tab
     */
    void initialize_tab_6();
    /**
     * initializes forum tab
     */
    void initialize_tab_7();

    Glib::RefPtr<Gdk::Pixbuf> m_backgroundImage1;
    Glib::RefPtr<Gdk::Pixbuf> m_backgroundImage2;
    Glib::RefPtr<Gdk::Pixbuf> m_backgroundImage3;
    Glib::RefPtr<Gdk::Pixbuf> m_backgroundImage4;
    Glib::RefPtr<Gdk::Pixbuf> m_backgroundImage5;
    Glib::RefPtr<Gdk::Pixbuf> m_backgroundImage6;

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


    //tab4
    Gtk::Entry* m_napspot_name;
    Gtk::ComboBoxText* m_combo_attr1;
    Gtk::ComboBoxText* m_combo_attr2;
    Gtk::ComboBoxText* m_combo_attr3;
    Gtk::TreeView m_treeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

    // tab 5
    Gtk::Entry* m_entry_napspot_id;
    Gtk::TreeView m_treeView_reviews;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel_reviews;

    //tab 6
    Gtk::Box tab_box_6;
    Gtk::Entry* m_entry_user_id;
    Gtk::TreeView m_treeView_reservations;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel_reservations;

    //declare variable for tab7
    Gtk::TextView forum_text_view;
    Gtk::Entry forum_text_entry;
    Gtk::Button post_comment_button;
    Gtk::Box posts_container;
    std::vector<std::pair<std::string, std::vector<Comment>>> forum_posts;
    std::vector<std::pair<Gtk::Button*, std::string>> comment_buttons;



    //reservation model columns
    class ModelColumnsReservations : public Gtk::TreeModel::ColumnRecord {
    public:
        ModelColumnsReservations() {
            add(m_col_reservation_id);
            add(m_col_napspot_id);
            add(m_col_start_time);
        }

        Gtk::TreeModelColumn<int> m_col_reservation_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_napspot_id;
        Gtk::TreeModelColumn<Glib::ustring> m_col_start_time;
    };

    ModelColumnsReservations m_columns_reservations;

    //napspots model columns
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

    //reviews model column
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

    ModelColumnsReviews m_columns_reviews;
};

#endif // BUTTONWINDOW_H