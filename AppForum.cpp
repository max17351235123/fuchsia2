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

    // Create the forum text entry
    forum_text_entry.set_placeholder_text("Enter your message...");

    // Create the post/comment button
    Gtk::Button post_comment_button("Post");
    post_comment_button.signal_clicked().connect(
            sigc::mem_fun(*this, &AppForum::on_post_comment_button_clicked)
    );

    // Pack the widgets into the box
    pack_start(forum_text_view);
    pack_start(forum_text_entry);
    pack_start(post_comment_button);

    // Create the comment button container and pack it
    pack_start(comment_button_container);

    // Add some initial posts
    forum_posts.emplace_back("Initial Post 1", std::vector<Comment>());
    forum_posts.emplace_back("Initial Post 2", std::vector<Comment>());

    // Update the forum text view with the initial posts
    update_forum_text_view();

    // Show all child widgets
    show_all_children();
}

AppForum::~AppForum() {}

void AppForum::on_post_comment_button_clicked()
{
    // Get the text from the forum text entry
    Glib::ustring text = forum_text_entry.get_text();

    if (!text.empty()) {
        // If there's text, treat it as a new post
        forum_posts.emplace_back(text, std::vector<Comment>());

        // Clear the forum text entry
        forum_text_entry.set_text("");

        // Update the forum text view with the new post
        update_forum_text_view();
    } else {
        // If there's no text, treat it as a comment
        Gtk::Button comment_button("Comment");
        comment_button.signal_clicked().connect(
                sigc::mem_fun(*this, &AppForum::on_comment_button_clicked)
        );

        // Add the comment button to the container
        comment_button_container.pack_start(comment_button);

        // Show all child widgets
        show_all_children();
    }
}

void AppForum::on_comment_button_clicked(const std::string& post_text)
{
    // Get the comment text from the forum text entry
    Glib::ustring comment_text = " " + forum_text_entry.get_text(); // Add a space before the comment text

    // Find the post to comment on
    for (auto& post_pair : forum_posts) {
        if (post_pair.first == post_text) {
            // Add the comment to the post's comment vector
            post_pair.second.push_back({comment_text});
            break;
        }
    }

    // Clear the forum text entry
    forum_text_entry.set_text("");

    // Update the forum text view with the new comment
    update_forum_text_view();

    // Show all child widgets
    show_all_children();
}

void AppForum::update_forum_text_view() {
    Glib::ustring forum_content;
    for (const auto& post_pair : forum_posts) {
        const std::string& post = post_pair.first;
        forum_content += post + "\n";
        for (const auto& comment : post_pair.second) {
            forum_content += "    " + comment.text + "\n";
        }
    }
    forum_text_view.get_buffer()->set_text(forum_content);
}