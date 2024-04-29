//
// Created by laure on 2024/4/15.
//

#ifndef FUCHSIA2_APPFORUM_H
#define FUCHSIA2_APPFORUM_H

#include <gtkmm.h>
#include <vector>
#include <string>

struct Comment {
    std::string text;
    // Add any other necessary fields for comments
};

class AppForum : public Gtk::Box
{
public:
    AppForum();
    virtual ~AppForum();

protected:
    Gtk::TextView forum_text_view;
    Gtk::Entry forum_text_entry;
    Gtk::Button forum_post_button;

    std::vector<std::pair<std::string, std::vector<Comment>>> forum_posts;

    void on_forum_post_button_clicked();
    void on_comment_button_clicked(const std::string& post_text);
};

#endif //FUCHSIA2_APPFORUM_H