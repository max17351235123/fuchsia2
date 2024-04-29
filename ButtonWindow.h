#ifndef BUTTONWINDOW_H
#define BUTTONWINDOW_H

#include <gtkmm.h>

class ButtonWindow : public Gtk::Window {
public:
    ButtonWindow();

private:
    void on_button_clicked(const std::string& dbPath, const std::string& tableName, const std::string& attribute);
};

#endif // BUTTONWINDOW_H