#include "ButtonWindow.h"
#include "DatabaseWindow.h"
#include "Napspot.h"

extern Napspot ns;

ButtonWindow::ButtonWindow() {
    set_title("Choose an Attribute");
    set_default_size(400, 200);

    // Create a grid for the buttons
    auto grid = Gtk::make_managed<Gtk::Grid>();
    add(*grid);

    // Create the buttons
    auto warmButton = Gtk::make_managed<Gtk::Button>("Warm");
    auto chillyButton = Gtk::make_managed<Gtk::Button>("Chilly");
    auto quietButton = Gtk::make_managed<Gtk::Button>("Quiet");
    auto noisyButton = Gtk::make_managed<Gtk::Button>("Noisy");
    auto darkButton = Gtk::make_managed<Gtk::Button>("Dark");
    auto brightButton = Gtk::make_managed<Gtk::Button>("Bright");

    // Connect buttons to open new window
    warmButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "warm"));
    chillyButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "chilly"));
    quietButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "quiet"));
    noisyButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "noisy"));
    darkButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "dark"));
    brightButton->signal_clicked().connect(sigc::bind<std::string, std::string>(sigc::mem_fun(*this, &ButtonWindow::on_button_clicked), "../database/napspots.sqlite", "filtered_napspots", "bright"));

    // Add the buttons to the grid
    grid->attach(*warmButton, 0, 0, 1, 1);
    grid->attach(*chillyButton, 2, 0, 1, 1);
    grid->attach(*quietButton, 0, 1, 1, 1);
    grid->attach(*noisyButton, 2, 1, 1, 1);
    grid->attach(*darkButton, 0, 2, 1, 1);
    grid->attach(*brightButton, 2, 2, 1, 1);

    grid->set_column_homogeneous(true);
    grid->set_row_homogeneous(true);

    // Show all widgets
    show_all_children();
}

void ButtonWindow::on_button_clicked(const std::string& dbPath, const std::string& tableName, const std::string& attribute) {
    ns.filter_by_attribute(attribute);
    auto* dbWindow = new DatabaseWindow(dbPath, tableName);
    dbWindow->show();
}