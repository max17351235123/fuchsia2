#include "ButtonWindow.h"
#include "DatabaseWindow.h"
#include "Napspot.h"

extern Napspot ns;
extern Database db;

ButtonWindow::ButtonWindow()
        : m_VBox(Gtk::ORIENTATION_VERTICAL)
{
    set_title("Choose an Attribute");
    set_default_size(1200, 600);
    /*
    m_backgroundImage1 = Gdk::Pixbuf::create_from_file("path/to/image1.png");
    m_backgroundImage2 = Gdk::Pixbuf::create_from_file("path/to/image2.png");
    m_backgroundImage3 = Gdk::Pixbuf::create_from_file("path/to/image3.png");
    m_backgroundImage4 = Gdk::Pixbuf::create_from_file("path/to/image4.png");
    m_backgroundImage5 = Gdk::Pixbuf::create_from_file("path/to/image5.png");
    m_backgroundImage6 = Gdk::Pixbuf::create_from_file("path/to/image6.png");
    */
    // Configure the notebook
    m_Notebook.set_border_width(10);

    // Add the notebook pages
    initialize_tab_1();
    initialize_tab_2();
    initialize_tab_4();
    initialize_tab_5();
    initialize_tab_6();
    initialize_tab_7();


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
        auto label_name = Gtk::make_managed<Gtk::Label>("Napspot name:");
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



void ButtonWindow::initialize_tab_4() {

    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 10);
    tab_box_4.add(*vbox);
    auto hbox_name = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10);
    vbox->pack_start(*hbox_name, Gtk::PACK_SHRINK);


    auto label_name = Gtk::make_managed<Gtk::Label>("Napspot Name:");
    hbox_name->pack_start(*label_name, Gtk::PACK_SHRINK);

    m_napspot_name = Gtk::make_managed<Gtk::Entry>();
    hbox_name->pack_start(*m_napspot_name, Gtk::PACK_EXPAND_WIDGET);

    //box1
    auto hbox_attr = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10);
    vbox->pack_start(*hbox_attr, Gtk::PACK_SHRINK);

    //labels for attributes
    auto label_attr1 = Gtk::make_managed<Gtk::Label>("Attributes:");
    hbox_attr->pack_start(*label_attr1, Gtk::PACK_SHRINK);

    //attr1
    m_combo_attr1 = Gtk::make_managed<Gtk::ComboBoxText>();
    m_combo_attr1->append("Warm");
    m_combo_attr1->append("Chilly");
    hbox_attr->pack_start(*m_combo_attr1, Gtk::PACK_SHRINK);
    //attr2
    m_combo_attr2 = Gtk::make_managed<Gtk::ComboBoxText>();
    m_combo_attr2->append("Quiet");
    m_combo_attr2->append("Noisy");
    hbox_attr->pack_start(*m_combo_attr2, Gtk::PACK_SHRINK);
    //attr3
    m_combo_attr3 = Gtk::make_managed<Gtk::ComboBoxText>();
    m_combo_attr3->append("Dark");
    m_combo_attr3->append("Bright");
    // Add more attributes as needed
    hbox_attr->pack_start(*m_combo_attr3, Gtk::PACK_SHRINK);


    auto button_add_napspot = Gtk::make_managed<Gtk::Button>("Add Napspot");
    button_add_napspot->signal_clicked().connect(sigc::mem_fun(*this, &ButtonWindow::on_add_napspot_clicked));
    vbox->pack_start(*button_add_napspot, Gtk::PACK_SHRINK);

    m_Notebook.append_page(tab_box_4, "Add Napspot");
}

void ButtonWindow::initialize_tab_5() {
    // Create a vertical box to hold the widgets
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 10);
    tab_box_5.add(*vbox);

    // Create a horizontal box for the Napspot ID entry
    auto hbox_entry = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10);
    vbox->pack_start(*hbox_entry, Gtk::PACK_SHRINK);

    // Create a label for the Napspot ID entry
    auto label_napspot_id = Gtk::make_managed<Gtk::Label>("Napspot name:");
    hbox_entry->pack_start(*label_napspot_id, Gtk::PACK_SHRINK);

    // Create an entry for the Napspot ID
    m_entry_napspot_id = Gtk::make_managed<Gtk::Entry>();
    hbox_entry->pack_start(*m_entry_napspot_id, Gtk::PACK_EXPAND_WIDGET);

    // Create a button to fetch reviews
    auto button_fetch_reviews = Gtk::make_managed<Gtk::Button>("Fetch Reviews");
    button_fetch_reviews->signal_clicked().connect(sigc::mem_fun(*this, &ButtonWindow::on_fetch_reviews_clicked));
    vbox->pack_start(*button_fetch_reviews, Gtk::PACK_SHRINK);

    // Create a tree model and tree view for reviews
    m_refTreeModel_reviews = Gtk::ListStore::create(m_columns_reviews);
    m_treeView_reviews.set_model(m_refTreeModel_reviews);
    m_treeView_reviews.append_column("Review ID", m_columns_reviews.m_col_review_id);
    m_treeView_reviews.append_column("User ID", m_columns_reviews.m_col_user_id);
    m_treeView_reviews.append_column("Text", m_columns_reviews.m_col_text);
    m_treeView_reviews.append_column("Rating", m_columns_reviews.m_col_rating);

    // Create a scrolled window and add the tree view
    auto scrolledWindow_reviews = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolledWindow_reviews->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledWindow_reviews->add(m_treeView_reviews);
    vbox->pack_start(*scrolledWindow_reviews, Gtk::PACK_EXPAND_WIDGET);

    // Set the tree view to expand and fill the available space
    m_treeView_reviews.set_hexpand(true);
    m_treeView_reviews.set_vexpand(true);

    // Set the vbox to expand and fill the tab
    vbox->set_hexpand(true);
    vbox->set_vexpand(true);

    // Add the fifth tab to the notebook
    m_Notebook.append_page(tab_box_5, "Reviews");
}

void ButtonWindow::initialize_tab_6() {
    // Create a vertical box to hold the widgets
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_VERTICAL, 10);
    tab_box_6.add(*vbox);

    // Create a horizontal box for the User ID entry
    auto hbox_entry = Gtk::make_managed<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL, 10);
    vbox->pack_start(*hbox_entry, Gtk::PACK_SHRINK);

    // Create a label for the User ID entry
    auto label_user_id = Gtk::make_managed<Gtk::Label>("Username:");
    hbox_entry->pack_start(*label_user_id, Gtk::PACK_SHRINK);

    // Create an entry for the User ID
    m_entry_user_id = Gtk::make_managed<Gtk::Entry>();
    hbox_entry->pack_start(*m_entry_user_id, Gtk::PACK_EXPAND_WIDGET);

    // Create a button to fetch reservations
    auto button_fetch_reservations = Gtk::make_managed<Gtk::Button>("Fetch Reservations");
    button_fetch_reservations->signal_clicked().connect(sigc::mem_fun(*this, &ButtonWindow::on_fetch_reservations_clicked));
    vbox->pack_start(*button_fetch_reservations, Gtk::PACK_SHRINK);

    // Create a tree model and tree view for reservations
    m_refTreeModel_reservations = Gtk::ListStore::create(m_columns_reservations);
    m_treeView_reservations.set_model(m_refTreeModel_reservations);
    m_treeView_reservations.append_column("Reservation ID", m_columns_reservations.m_col_reservation_id);
    m_treeView_reservations.append_column("Napspot ID", m_columns_reservations.m_col_napspot_id);
    m_treeView_reservations.append_column("Start Time", m_columns_reservations.m_col_start_time);

    // Create a scrolled window and add the tree view
    auto scrolledWindow_reservations = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolledWindow_reservations->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolledWindow_reservations->add(m_treeView_reservations);
    vbox->pack_start(*scrolledWindow_reservations, Gtk::PACK_EXPAND_WIDGET);

    // Set the tree view to expand and fill the available space
    m_treeView_reservations.set_hexpand(true);
    m_treeView_reservations.set_vexpand(true);

    // Set the vbox to expand and fill the tab
    vbox->set_hexpand(true);
    vbox->set_vexpand(true);

    // Add the sixth tab to the notebook
    m_Notebook.append_page(tab_box_6, "Reservations");
}

void ButtonWindow::initialize_tab_7() {
    // Configure the container for posts and buttons
    posts_container.set_orientation(Gtk::ORIENTATION_VERTICAL);
    posts_container.set_spacing(5);
    posts_container.set_border_width(10);

    // Ensure the forum text view is properly initialized and packed
    forum_text_view.set_editable(false);  // Assuming it's for display only
    auto scrolled_window = Gtk::make_managed<Gtk::ScrolledWindow>();
    scrolled_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled_window->add(forum_text_view);
    posts_container.pack_start(*scrolled_window, Gtk::PACK_EXPAND_WIDGET);

    // Set up the entry and post button for new posts
    forum_text_entry.set_placeholder_text("Write something...");
    post_comment_button.set_label("Post");
    post_comment_button.signal_clicked().connect(sigc::mem_fun(*this, &ButtonWindow::on_post_comment_button_clicked));

    // Pack the entry and button into the container
    posts_container.pack_start(forum_text_entry, Gtk::PACK_SHRINK);
    posts_container.pack_start(post_comment_button, Gtk::PACK_SHRINK);

    // Add the entire posts container to the notebook page
    m_Notebook.append_page(posts_container, "Forum");

    // Show all children ensures that all widgets are visible
    posts_container.show_all_children();
}



void ButtonWindow::on_fetch_reservations_clicked() {
    // Get the entered User ID
    string user_id = db.query("users","user_id","username", m_entry_user_id->get_text());

    // Clear the existing reservations from the tree model
    m_refTreeModel_reservations->clear();

    // Fetch reservations from the database based on the User ID
    sqlite3* db;
    int rc = sqlite3_open("../database/napspots.sqlite", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::string query = "SELECT reservation_id, napspot_id, start_time FROM reservations WHERE user_id = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, user_id.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int reservation_id = sqlite3_column_int(stmt, 0);
        std::string napspot_id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string start_time = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

        Gtk::TreeModel::Row row = *(m_refTreeModel_reservations->append());
        row[m_columns_reservations.m_col_reservation_id] = reservation_id;
        row[m_columns_reservations.m_col_napspot_id] = napspot_id;
        row[m_columns_reservations.m_col_start_time] = start_time;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void ButtonWindow::on_fetch_reviews_clicked() {
    // Get the entered Napspot ID
    string napspot_id = db.query("users","user_id","username", m_entry_napspot_id->get_text());

    // Clear the existing reviews from the tree model
    m_refTreeModel_reviews->clear();

    // Fetch reviews from the database based on the Napspot ID
    sqlite3* db;
    int rc = sqlite3_open("../database/napspots.sqlite", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::string query = "SELECT * FROM reviews WHERE napspot_id = ?";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_text(stmt, 1, napspot_id.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int review_id = sqlite3_column_int(stmt, 0);
        std::string user_id = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        int rating = sqlite3_column_int(stmt, 4);

        Gtk::TreeModel::Row row = *(m_refTreeModel_reviews->append());
        row[m_columns_reviews.m_col_review_id] = review_id;
        row[m_columns_reviews.m_col_user_id] = user_id;
        row[m_columns_reviews.m_col_text] = text;
        row[m_columns_reviews.m_col_rating] = rating;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void ButtonWindow::on_add_napspot_clicked() {
    // Get the Napspot Name from the entry
    Glib::ustring napspot_name = m_napspot_name->get_text();
    vector<string> attribute;
    // Get the selected Rating from the combo box
    attribute.push_back((m_combo_attr1->get_active_text()));

    // Get the selected Rating from the combo box
    attribute.push_back((m_combo_attr2->get_active_text()));

    // Get the selected Rating from the combo box
    attribute.push_back((m_combo_attr3->get_active_text()));

    // Call a method to process the review

    ns.add_napspot(napspot_name,attribute);

    Gtk::MessageDialog dialog(*this, "Napspot Added!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
    dialog.run();
}

void ButtonWindow::on_button_clicked(const std::string& dbPath, const std::string& tableName, const std::string& attribute) {
    ns.filter_by_attribute(attribute);
    auto* dbWindow = new DatabaseWindow(dbPath, tableName);
    dbWindow->show();
}

void ButtonWindow::on_submit_review() {
    // Get the Napspot Name from the entry
    string napspot_name = db.query("users","user_id","username", m_entry_name->get_text());

    // Get the Review from the text view
    Glib::ustring review = m_text_view->get_buffer()->get_text();

    // Get the selected Rating from the combo box
    int rating = std::stoi(m_combo_rating->get_active_text());

    // Call a method to process the review
    ns.add_review(napspot_name, review, rating);

    Gtk::MessageDialog dialog(*this, "Review Submitted!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
    dialog.run();
}



void ButtonWindow::on_comment_button_clicked(std::string post_text) {
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


void ButtonWindow::update_forum_text_view() {
    Glib::ustring forum_content;
    for (const auto& post_pair : forum_posts) {
        forum_content += post_pair.first + "\n";
        for (const auto& comment : post_pair.second) {
            forum_content += "    " + comment.text + "\n";
        }
    }
    forum_text_view.get_buffer()->set_text(forum_content);


}


void ButtonWindow::on_post_comment_button_clicked() {
    std::string text = forum_text_entry.get_text();
    if (!text.empty()) {
        add_post_with_comment_button(text);
        forum_text_entry.set_text("");
        update_forum_text_view();
    } else {
        std::cout << "No text entered." << std::endl;
    }
}


void ButtonWindow::add_post_with_comment_button(const std::string& post_text) {
    forum_posts.emplace_back(post_text, std::vector<Comment>());


    // Create a new comment button for this post
    Gtk::Button* comment_button = new Gtk::Button("Comment on: " + post_text);
    comment_button->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &ButtonWindow::on_comment_button_clicked), post_text));
    posts_container.pack_start(*comment_button, Gtk::PACK_SHRINK);
    comment_button->show();


    comment_buttons.emplace_back(comment_button, post_text);
}
