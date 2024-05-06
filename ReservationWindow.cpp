#include "ReservationWindow.h"
#include "Napspot.h"
#include <iostream>

extern Napspot ns;
extern Database db;

ReservationWindow::ReservationWindow(const int& id)
        : Gtk::Window(),
          m_vbox(Gtk::ORIENTATION_VERTICAL, 10),
          combo_month(Gtk::manage(new Gtk::ComboBoxText())),
          combo_year(Gtk::manage(new Gtk::ComboBoxText())),
          combo_day_first(Gtk::manage(new Gtk::ComboBoxText())),
          combo_day_second(Gtk::manage(new Gtk::ComboBoxText())),
          combo_time(Gtk::manage(new Gtk::ComboBoxText())),
          combo_am_pm(Gtk::manage(new Gtk::ComboBoxText())),
          id(id)
{
    this->id = id;
    set_title("Reservation Window");
    set_default_size(400, 300);

    // Create a label for the window
    auto label = Gtk::manage(new Gtk::Label("Select Date and Time"));
    m_vbox.pack_start(*label, Gtk::PACK_SHRINK);

    // Create a horizontal box for the month and year combo boxes
    auto hbox_month_year = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 10));
    m_vbox.pack_start(*hbox_month_year, Gtk::PACK_SHRINK);

    // Create a combo box for selecting the month
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
    for (int i = 2024; i <= 2034; ++i) {
        combo_year->append(std::to_string(i));
    }
    combo_year->set_active(0);
    hbox_month_year->pack_start(*combo_year, Gtk::PACK_EXPAND_WIDGET);

    // Create a horizontal box for the day combo boxes
    auto hbox_day = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    m_vbox.pack_start(*hbox_day, Gtk::PACK_SHRINK);

    // Create combo boxes for selecting the day (first and second digits)
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
    auto hbox_time = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    m_vbox.pack_start(*hbox_time, Gtk::PACK_SHRINK);

    // Create a combo box for selecting the time (1-hour increments)
    for (int i = 0; i <= 12; ++i) {
        std::string time = std::to_string(i) + ":00";
        combo_time->append(time);
    }
    combo_time->set_active(0);
    hbox_time->pack_start(*combo_time, Gtk::PACK_EXPAND_WIDGET);

    // Create a combo box for selecting AM or PM
    combo_am_pm->append("AM");
    combo_am_pm->append("PM");
    combo_am_pm->set_active(0);
    hbox_time->pack_start(*combo_am_pm, Gtk::PACK_SHRINK);

    // Create a button to get the formatted date-time string
    auto button_get_datetime = Gtk::manage(new Gtk::Button("Reserve"));
    button_get_datetime->signal_clicked().connect(sigc::mem_fun(*this, &ReservationWindow::on_button_reserve_clicked));
    m_vbox.pack_start(*button_get_datetime, Gtk::PACK_SHRINK);

    add(m_vbox);

    // Show all widgets
    show_all_children();
}

void ReservationWindow::on_button_reserve_clicked() {
    if (combo_month && combo_year && combo_day_first && combo_day_second && combo_time && combo_am_pm) {
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
        m_formatted_datetime = month + "/" + day + "/" + year + "/" + time + " " + am_pm;

        // Print the formatted date-time string (for demonstration purposes)
        std::cout << "Formatted Date-Time: " << m_formatted_datetime << std::endl;
    } else {
        std::cerr << "Error: One or more combo box pointers are null." << std::endl;
    }
    if (db.query("reservations", "napspot_id", "start_time", m_formatted_datetime)==to_string(id)) {
        Gtk::MessageDialog dialog(*this, "There is already a reservation at this time!", false,
                                  Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.run();
    } else {
        ns.add_reservation(to_string(id),m_formatted_datetime);
        Gtk::MessageDialog dialog(*this, "Reservation made. Hope you're feeling eepy!", false,
                                  Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);

        dialog.run();
    }
}

Glib::ustring ReservationWindow::get_formatted_datetime() const {
    return m_formatted_datetime;
}
