#include "ButtonWindow.h"
#include "DatabaseWindow.h"
#include "Napspot.h"

extern Napspot ns;

ButtonWindow::ButtonWindow()
        : m_VBox(Gtk::ORIENTATION_VERTICAL)
{
    set_title("Choose an Attribute");
    set_default_size(1200, 600);

    // Configure the notebook
    m_Notebook.set_border_width(10);

    // Add the notebook pages
    initialize_tab_1();
    initialize_tab_2();
    initialize_tab_3();
    initialize_tab_4();

    // Add the notebook to the vertical box
    m_VBox.pack_start(m_Notebook);

    // Add the vertical box to the window
    add(m_VBox);

    // Show all widgets
    show_all_children();
}

void ButtonWindow::initialize_tab_1() {
    // Create a grid for the buttons
    auto grid = Gtk::make_managed<Gtk::Grid>();
    tab_box_1.add(*grid);

    // Create the buttons
    auto warmButton = Gtk::make_managed<Gtk::Button>("Warm");
    auto chillyButton = Gtk::make_managed<Gtk::Button>("Chilly");
    auto quietButton = Gtk::make_managed<Gtk::Button>("Quiet");
    auto noisyButton = Gtk::make_managed<Gtk::Button>("Noisy");
    auto darkButton = Gtk::make_managed<Gtk::Button>("Dark");
    auto brightButton = Gtk::make_managed<Gtk::Button>("Bright");

    // Set button properties to expand and fill the grid cells
    warmButton->set_hexpand(true);
    warmButton->set_vexpand(true);
    chillyButton->set_hexpand(true);
    chillyButton->set_vexpand(true);
    quietButton->set_hexpand(true);
    quietButton->set_vexpand(true);
    noisyButton->set_hexpand(true);
    noisyButton->set_vexpand(true);
    darkButton->set_hexpand(true);
    darkButton->set_vexpand(true);
    brightButton->set_hexpand(true);
    brightButton->set_vexpand(true);

    // Connect buttons to open new window
    warmButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "warm"));
    chillyButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "chilly"));
    quietButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "quiet"));
    noisyButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "noisy"));
    darkButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "dark"));
    brightButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "bright"));

    // Add the buttons to the grid
    grid->attach(*warmButton, 0, 0, 1, 1);
    grid->attach(*chillyButton, 1, 0, 1, 1);
    grid->attach(*quietButton, 0, 1, 1, 1);
    grid->attach(*noisyButton, 1, 1, 1, 1);
    grid->attach(*darkButton, 0, 2, 1, 1);
    grid->attach(*brightButton, 1, 2, 1, 1);

    // Set column and row spacing for the grid
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);

    // Set the grid to expand and fill the tab box
    grid->set_hexpand(true);
    grid->set_vexpand(true);

    m_Notebook.append_page(tab_box_1, "Attribute Selection");
}

void ButtonWindow::initialize_tab_2() {

        // Create a vertical box to hold the widgets
        auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 10);
        tab_box_2.add(*vbox);

        // Create a horizontal box for the Napspot Name label and entry
        auto hbox_name = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10);
        vbox->pack_start(*hbox_name, Gtk::PACK_SHRINK);

        // Create a label for the Napspot Name
        auto label_name = Gtk::make_managed<Gtk::Label>("Napspot ID:");
        hbox_name->pack_start(*label_name, Gtk::PACK_SHRINK);

        // Create an entry for the Napspot Name
        m_entry_name = Gtk::make_managed<Gtk::Entry>();
        hbox_name->pack_start(*m_entry_name, Gtk::PACK_EXPAND_WIDGET);

        // Create a label for the Review
        auto label_review = Gtk::make_managed<Gtk::Label>("Review:");
        vbox->pack_start(*label_review, Gtk::PACK_SHRINK);

        // Create a scroll window for the Review text view
        auto scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
        scrolled_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        scrolled_window->set_shadow_type(Gtk::SHADOW_IN);
        vbox->pack_start(*scrolled_window, Gtk::PACK_EXPAND_WIDGET);

        // Create a text view for the Review
        m_text_view = Gtk::make_managed<Gtk::TextView>();
        m_text_view->set_wrap_mode(Gtk::WRAP_WORD);
        scrolled_window->add(*m_text_view);

        // Create a horizontal box for the Rating label and combo box
        auto hbox_rating = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10);
        vbox->pack_start(*hbox_rating, Gtk::PACK_SHRINK);

        // Create a label for the Rating
        auto label_rating = Gtk::make_managed<Gtk::Label>("Rating:");
        hbox_rating->pack_start(*label_rating, Gtk::PACK_SHRINK);

        // Create a combo box for the Rating
        m_combo_rating = Gtk::make_managed<Gtk::ComboBoxText>();
        for (int i = 1; i <= 10; ++i) {
            m_combo_rating->append(std::to_string(i));
        }
        m_combo_rating->set_active(0);
        hbox_rating->pack_start(*m_combo_rating, Gtk::PACK_SHRINK);

        // Create a button to submit the review
        auto button_submit = Gtk::make_managed<Gtk::Button>("Submit Review");
        button_submit->signal_clicked().connect(sigc::mem_fun(*this, &ButtonWindow::on_submit_review));
        vbox->pack_start(*button_submit, Gtk::PACK_SHRINK);



        m_Notebook.append_page(tab_box_2, "Write a Review");
    }

void ButtonWindow::initialize_tab_3() {

    // Create a vertical box to hold the widgets
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 10);
    tab_box_3.add(*vbox);

    // Create a label for the tab
    auto label = Gtk::make_managed<Gtk::Label>("Select Date and Time");
    vbox->pack_start(*label, Gtk::PACK_SHRINK);

    // Create a horizontal box for the month and year combo boxes
    auto hbox_month_year = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10);
    vbox->pack_start(*hbox_month_year, Gtk::PACK_SHRINK);

    // Create a combo box for selecting the month
    combo_month = Gtk::make_managed<Gtk::ComboBoxText>();
    combo_month->append("January");
    combo_month->append("February");
    combo_month->append("March");
    combo_month->append("April");
    combo_month->append("May");
    combo_month->append("June");
    combo_month->append("July");
    combo_month->append("August");
    combo_month->append("September");
    combo_month->append("October");
    combo_month->append("November");
    combo_month->append("December");
    combo_month->set_active(0);
    hbox_month_year->pack_start(*combo_month, Gtk::PACK_EXPAND_WIDGET);

    // Create a combo box for selecting the year
    combo_year = Gtk::make_managed<Gtk::ComboBoxText>();
    for (int i = 2024; i <= 2034; ++i) {
        combo_year->append(std::to_string(i));
    }
    combo_year->set_active(0);
    hbox_month_year->pack_start(*combo_year, Gtk::PACK_EXPAND_WIDGET);

    // Create a horizontal box for the day combo boxes
    auto hbox_day = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 5);
    vbox->pack_start(*hbox_day, Gtk::PACK_SHRINK);

    // Create combo boxes for selecting the day (first and second digits)
    combo_day_first = Gtk::make_managed<Gtk::ComboBoxText>();
    combo_day_second = Gtk::make_managed<Gtk::ComboBoxText>();
    for (int i = 0; i <= 3; ++i) {
        combo_day_first->append(std::to_string(i));
    }
    for (int i = 0; i <= 9; ++i) {
        combo_day_second->append(std::to_string(i));
    }
    combo_day_first->set_active(0);
    combo_day_second->set_active(0);
    hbox_day->pack_start(*combo_day_first, Gtk::PACK_SHRINK);
    hbox_day->pack_start(*combo_day_second, Gtk::PACK_SHRINK);

    // Create a horizontal box for the time combo box and AM/PM combo box
    auto hbox_time = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 5);
    vbox->pack_start(*hbox_time, Gtk::PACK_SHRINK);

    // Create a combo box for selecting the time (1-hour increments)
    combo_time = Gtk::make_managed<Gtk::ComboBoxText>();
    combo_time->append("12:00");
    for (int i = 1; i <= 11; ++i) {
        std::string time = std::to_string(i) + ":00";
        combo_time->append(time);
    }
    combo_time->set_active(0);
    hbox_time->pack_start(*combo_time, Gtk::PACK_EXPAND_WIDGET);

    // Create a combo box for selecting AM or PM
    combo_am_pm = Gtk::make_managed<Gtk::ComboBoxText>();
    combo_am_pm->append("AM");
    combo_am_pm->append("PM");
    combo_am_pm->set_active(0);
    hbox_time->pack_start(*combo_am_pm, Gtk::PACK_SHRINK);

    auto button_get_datetime = Gtk::make_managed<Gtk::Button>("Get Date-Time");
    button_get_datetime->signal_clicked().connect(sigc::mem_fun(*this, &ButtonWindow::on_button_get_datetime_clicked));
    vbox->pack_start(*button_get_datetime, Gtk::PACK_SHRINK);

    // Add the third tab to the notebook
    m_Notebook.append_page(tab_box_3, "Select Date and Time");
}
void ButtonWindow::initialize_tab_4() {
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

}


void ButtonWindow::on_button_clicked(const std::string& dbPath, const std::string& tableName, const std::string& attribute) {
    ns.filter_by_attribute(attribute);
    auto* dbWindow = new DatabaseWindow(dbPath, tableName);
    dbWindow->show();
}

void ButtonWindow::on_submit_review() {
    // Get the Napspot Name from the entry
    Glib::ustring napspot_name = m_entry_name->get_text();

    // Get the Review from the text view
    Glib::ustring review = m_text_view->get_buffer()->get_text();

    // Get the selected Rating from the combo box
    int rating = std::stoi(m_combo_rating->get_active_text());

    // Call a method to process the review
    ns.add_review(napspot_name, review, rating);

    Gtk::MessageDialog dialog(*this, "Review Submitted!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
    dialog.run();
}

void ButtonWindow::on_button_get_datetime_clicked() {

    // Get the selected month
    Glib::ustring month = combo_month->get_active_text();

    // Get the selected day
    Glib::ustring day = combo_day_first->get_active_text() + combo_day_second->get_active_text();

    // Get the selected year
    Glib::ustring year = combo_year->get_active_text();

    // Get the selected time
    Glib::ustring time = combo_time->get_active_text();

    // Get the selected AM/PM
    Glib::ustring am_pm = combo_am_pm->get_active_text();

    // Format the date-time string
    Glib::ustring m_formatted_datetime = month + "/" + day + "/" + year + "/" + time + "/" + am_pm;

    // Print the formatted date-time string (for demonstration purposes)
    std::cout << "Formatted Date-Time: "+ m_formatted_datetime  << std::endl;


}