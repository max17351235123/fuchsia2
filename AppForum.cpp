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

    // Create the forum text entry and post button
    forum_text_entry.set_placeholder_text("Enter your message...");
    forum_post_button.set_label("Post");

    // Connect the post button signal to the on_forum_post_button_clicked function
    forum_post_button.signal_clicked().connect(
            sigc::mem_fun(*this, &AppForum::on_forum_post_button_clicked)
    );

    // Pack the widgets into the box
    pack_start(forum_text_view);
    pack_start(forum_text_entry);
    pack_start(forum_post_button);
}

AppForum::~AppForum()
{
}

void AppForum::on_forum_post_button_clicked()
{
    // Get the text from the forum text entry
    Glib::ustring post_text = forum_text_entry.get_text();

    // Add the post to the forum posts vector
    forum_posts.emplace_back(post_text, std::vector<Comment>());

    // Clear the forum text entry
    forum_text_entry.set_text("");

    // Add a comment button for the new post
    Gtk::Button comment_button;
    comment_button.set_label("Comment");
    comment_button.signal_clicked().connect(
            sigc::bind<std::string>(
                    sigc::mem_fun(*this, &AppForum::on_comment_button_clicked),
                    post_text
            )
    );

    // Pack the comment button into the box
    pack_start(comment_button);

    // Update the forum text view with the new posts
    Glib::ustring forum_content;
    for (const auto& post_pair : forum_posts)
    {
        const std::string& post = post_pair.first;
        forum_content += post + "\n";
        for (const auto& comment : post_pair.second)
        {
            forum_content += "    " + comment.text + "\n";
        }
    }
    forum_text_view.get_buffer()->set_text(forum_content);
}

void AppForum::on_comment_button_clicked(const std::string& post_text)
{
    // Get the comment text from the forum text entry
    Glib::ustring comment_text = forum_text_entry.get_text();

    // Find the post to comment on
    for (auto& post_pair : forum_posts)
    {
        if (post_pair.first == post_text)
        {
            // Add the comment to the post's comment vector
            post_pair.second.push_back({comment_text});
            break;
        }
    }

    // Clear the forum text entry
    forum_text_entry.set_text("");

    // Update the forum text view with the new comments
    Glib::ustring forum_content;
    for (const auto& post_pair : forum_posts)
    {
        const std::string& post = post_pair.first;
        forum_content += post + "\n";
        for (const auto& comment : post_pair.second)
        {
            forum_content += "    " + comment.text + "\n";
        }
    }
    forum_text_view.get_buffer()->set_text(forum_content);
}