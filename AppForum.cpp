#include "AppForum.h"
#include <iostream>

AppForum::AppForum()
        : Gtk::Box(Gtk::ORIENTATION_VERTICAL),
          post_comment_button("Post")
{
    initUI();
}

AppForum::~AppForum() {
    for (auto& button_pair : comment_buttons) {
        delete button_pair.first; // Ensure we clean up dynamically created buttons
    }
}

void AppForum::initUI() {
    // Set up the forum text view and make it read-only
    forum_text_view.set_editable(false);
    forum_text_view.set_cursor_visible(false);

    // Set placeholder text for the entry where users type their message
    forum_text_entry.set_placeholder_text("Enter your message...");

    // Set up the post/comment button
    post_comment_button.signal_clicked().connect(sigc::mem_fun(*this, &AppForum::on_post_comment_button_clicked));

    // Pack the widgets into the vertical box
    pack_start(forum_text_view, Gtk::PACK_EXPAND_WIDGET);
    pack_start(forum_text_entry, Gtk::PACK_SHRINK);
    pack_start(post_comment_button, Gtk::PACK_SHRINK);
    pack_start(posts_container, Gtk::PACK_EXPAND_WIDGET); // Container for posts and comment buttons

    // Update the display to show initial posts
    update_forum_text_view();

    // Ensure all child widgets are shown
    show_all_children();
}

void AppForum::on_post_comment_button_clicked() {
    std::string text = forum_text_entry.get_text();
    if (!text.empty()) {
        add_post_with_comment_button(text);
        forum_text_entry.set_text("");
        update_forum_text_view();
    } else {
        std::cout << "No text entered." << std::endl;
    }
}

void AppForum::add_post_with_comment_button(const std::string& post_text) {
    forum_posts.emplace_back(post_text, std::vector<Comment>());

    // Create a new comment button for this post
    Gtk::Button* comment_button = new Gtk::Button("Comment on: " + post_text);
    comment_button->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &AppForum::on_comment_button_clicked), post_text));
    posts_container.pack_start(*comment_button, Gtk::PACK_SHRINK);
    comment_button->show();

    comment_buttons.emplace_back(comment_button, post_text);
}

void AppForum::on_comment_button_clicked(std::string post_text) {
    // Get comment text and update the forum
    std::string comment_text = forum_text_entry.get_text();
    if (!comment_text.empty()) {
        for (auto& post_pair : forum_posts) {
            if (post_pair.first == post_text) {
                post_pair.second.push_back(Comment{comment_text});
                break;
            }
        }
        forum_text_entry.set_text("");
        update_forum_text_view();
    } else {
        std::cout << "No comment entered." << std::endl;
    }
}

void AppForum::update_forum_text_view() {
    Glib::ustring forum_content;
    for (const auto& post_pair : forum_posts) {
        forum_content += post_pair.first + "\n";
        for (const auto& comment : post_pair.second) {
            forum_content += "    " + comment.text + "\n";
        }
    }
    forum_text_view.get_buffer()->set_text(forum_content);
}
