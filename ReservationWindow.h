#ifndef ReservationWindow_H
#define ReservationWindow_H

#include <gtkmm.h>
#include <gtkmm/comboboxtext.h>

class ReservationWindow : public Gtk::Window {
public:
    /**
     * Constructs a window for creating reservations at a certain napspot
     * @param id id of napspot ReservationWindow is being constructed for
     */
    ReservationWindow(const int& id);
    /**
     * Helper method for debugging
     * @return returns reservation String
     */
    Glib::ustring get_formatted_datetime() const;

private:
    /**
     * Adds all the time inputs the user chose to a string and creates a reservation for them if it
     * doesn't already exist at that napspot
     */
    void on_button_reserve_clicked();

    Gtk::ComboBoxText* combo_month;
    Gtk::ComboBoxText* combo_year;
    Gtk::ComboBoxText* combo_day_first;
    Gtk::ComboBoxText* combo_day_second;
    Gtk::ComboBoxText* combo_time;
    Gtk::ComboBoxText* combo_am_pm;
    int id;

    Glib::ustring m_formatted_datetime;
    Gtk::Box m_vbox;
};

#endif // ReservationWindow_H