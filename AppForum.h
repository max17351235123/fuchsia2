#ifndef APPFORUM_H
#define APPFORUM_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/textview.h>
#include <gtkmm/entry.h>
#include <vector>
#include <string>

struct Comment {
    std::string text;
};

class AppForum : public Gtk::Box {
public:
    AppForum();
    virtual ~AppForum();

protected:
    Gtk::TextView forum_text_view;
    Gtk::Entry forum_text_entry;
    Gtk::Button post_comment_button;
    Gtk::Box posts_container; // Use Gtk::Box instead of Gtk::VBox
    std::vector<std::pair<std::string, std::vector<Comment>>> forum_posts;
    std::vector<std::pair<Gtk::Button*, std::string>> comment_buttons; // Pair of buttons and the post text they correspond to

    void initUI();
    void on_post_comment_button_clicked();
    void on_comment_button_clicked(std::string post_text);
    void update_forum_text_view();
    void add_post_with_comment_button(const std::string& post_text);
};

#endif // APPFORUM_H
