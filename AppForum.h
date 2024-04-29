//
// Created by laure on 2024/4/15.
//

#ifndef APPFORUM_H
#define APPFORUM_H

#include <gtkmm.h>
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
    Gtk::VBox comment_button_container;
    std::vector<std::pair<std::string, std::vector<Comment>>> forum_posts;

    void on_post_comment_button_clicked();
    void on_comment_button_clicked(const std::string& post_text);
    void update_forum_text_view();
};

#endif // APPFORUM_H
