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
    initialize_tab_5();


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
    auto label_napspot_id = Gtk::make_managed<Gtk::Label>("Napspot ID:");
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
    scrolledWindow_reviews->add(m_treeView_reviews);
    vbox->pack_start(*scrolledWindow_reviews, Gtk::PACK_EXPAND_WIDGET);

    // Add the fifth tab to the notebook
    m_Notebook.append_page(tab_box_5, "Reviews");
}

void ButtonWindow::on_fetch_reviews_clicked() {
    // Get the entered Napspot ID
    std::string napspot_id = m_entry_napspot_id->get_text();

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