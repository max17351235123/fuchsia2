//
// Created by laure on 2024/4/15.
//
// AppForum.h
#ifndef FUCHSIA2_APPFORUM_H
#define FUCHSIA2_APPFORUM_H

#include <gtkmm.h>
#include <vector>
#include <string>

struct ForumPost {
    std::string username;
    std::string message;
    std::vector<std::string> comments;
};

class AppForum : public Gtk::Box
{
public:
    AppForum();
    virtual ~AppForum();

protected:
    Gtk::TextView forum_text_view;
    Gtk::Entry forum_text_entry;
    Gtk::Entry username_entry;
    Gtk::Button forum_post_button;

    Gtk::Box post_box;
    Gtk::Box username_box;
    Gtk::Label username_label;

    std::vector<ForumPost> forum_posts;

    void on_forum_post_button_clicked();
    void on_comment_button_clicked(ForumPost& post, Gtk::Entry& comment_entry);
    void create_post_view(const ForumPost& post);
};

#endif //FUCHSIA2_APPFORUM_H