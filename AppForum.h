//
// Created by laure on 2024/4/15.
//

#ifndef FUCHSIA2_APPFORUM_H
#define FUCHSIA2_APPFORUM_H

#include <gtkmm.h>
#include <vector>
#include <string>

class AppForum : public Gtk::Box
{
public:
    AppForum();
    virtual ~AppForum();

protected:
    Gtk::TextView forum_text_view;
    Gtk::Entry forum_text_entry;
    Gtk::Button forum_post_button;

    std::vector<std::string> forum_posts;

    void on_forum_post_button_clicked();
};

#endif //FUCHSIA2_APPFORUM_H