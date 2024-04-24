//
// Created by laure on 2024/4/15.
//

#include "AppForum.h"

AppForum::AppForum()
        : Gtk::Box(Gtk::ORIENTATION_VERTICAL)
{
    // Create the forum text view and set it to be read-only
    forum_text_view.set_editable(false);
    forum_text_view.set_cursor_visible(false);
    forum_text_view.set_wrap_mode(Gtk::WRAP_WORD);

    // Create the forum text entry, username entry, and post button
    forum_text_entry.set_placeholder_text("Enter your message...");
    username_entry.set_placeholder_text("Enter your username...");
    forum_post_button.set_label("Post");

    // Connect the post button signal to the on_forum_post_button_clicked function
    forum_post_button.signal_clicked().connect(
            sigc::mem_fun(*this, &AppForum::on_forum_post_button_clicked)
    );

    // Pack the widgets into the box
    pack_start(forum_text_view);
    pack_start(username_entry);
    pack_start(forum_text_entry);
    pack_start(forum_post_button);
}

AppForum::~AppForum()
{
}

void AppForum::on_forum_post_button_clicked()
{
    // Get the text from the forum text entry and username entry
    std::string post_text = forum_text_entry.get_text();
    std::string username = username_entry.get_text();

    // Create a ForumPost struct and add it to the forum posts vector
    ForumPost post = {username, post_text};
    forum_posts.push_back(post);

    // Clear the forum text entry and username entry
    forum_text_entry.set_text("");
    username_entry.set_text("");

    // Create the post view and add it to the forum text view
    create_post_view(post);
}

void AppForum::create_post_view(const ForumPost& post)
{
    // Create the username box and label
    username_label.set_markup("<b>" + post.username + "</b>");
    username_box.pack_start(username_label, Gtk::PACK_SHRINK);

    // Create the post box and add the username box and message
    post_box.pack_start(username_box, Gtk::PACK_SHRINK);
    post_box.pack_start(*Gtk::manage(new Gtk::Label(post.message)), Gtk::PACK_SHRINK);

    // Create an EventBox and add the post box to it
    auto event_box = Gtk::manage(new Gtk::EventBox());
    event_box->add(post_box);

    // Add the event box to the text view
    Gtk::TextIter iter = forum_text_view.get_buffer()->end();
    Glib::RefPtr<Gtk::TextChildAnchor> anchor = forum_text_view.get_buffer()->create_child_anchor(iter);
    forum_text_view.add_child_at_anchor(*event_box, anchor);

    forum_text_view.get_buffer()->insert_at_cursor("\n");
}