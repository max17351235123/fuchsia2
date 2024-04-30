#ifndef ReservationWindow_H
#define ReservationWindow_H

#include <gtkmm.h>
#include <gtkmm/comboboxtext.h>

class ReservationWindow : public Gtk::Window {
public:
    ReservationWindow(const int& id);
    Glib::ustring get_formatted_datetime() const;

private:
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