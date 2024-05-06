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
    /**
     * Constructs a window for account creation and login using a username and password
     */
    MyWindow();

    Gtk::Entry* username_entry;
    Gtk::Entry* password_entry;
    UserCredentials credentials;

    /**
     * Calls authenticateUser from UserCredentials class, if correct creates an instance of ButtonWindow
     */
    void on_login_clicked();
    /**
     * Calls addCredential from UserCredentials class if authenticateUser returns correct int
     */
    void on_create_account_clicked();

};
#endif //EXAMPLE_03_MYWINDOW_H
