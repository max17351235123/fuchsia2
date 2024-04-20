//
// Created by pjsmi on 4/15/2024.
//

#ifndef EXAMPLE_03_MYWINDOW_H
#define EXAMPLE_03_MYWINDOW_H
#include <gtkmm/application.h>
#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/messagedialog.h>
#include "UserCredentials.h"

class MyWindow : public Gtk::Window {
public:
    MyWindow();

    Gtk::Entry* username_entry;
    Gtk::Entry* password_entry;
    UserCredentials credentials;

    void on_login_clicked();
    void on_create_account_clicked();

};
#endif //EXAMPLE_03_MYWINDOW_H
