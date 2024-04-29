//
// Created by pjsmi on 4/15/2024.
//

#include "MyWindow.h"
#include "ButtonWindow.h"


MyWindow::MyWindow()
    {
        set_title("Login");
        set_default_size(300, 200);

        Gtk::Box* box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
        add(*box);

        Gtk::Label* label1 = Gtk::manage(new Gtk::Label("Username:"));
        box->pack_start(*label1, Gtk::PACK_SHRINK);

        username_entry = Gtk::manage(new Gtk::Entry());
        box->pack_start(*username_entry, Gtk::PACK_SHRINK);

        Gtk::Label* label2 = Gtk::manage(new Gtk::Label("Password:"));
        box->pack_start(*label2, Gtk::PACK_SHRINK);

        password_entry = Gtk::manage(new Gtk::Entry());
        password_entry->set_visibility(false);
        box->pack_start(*password_entry, Gtk::PACK_SHRINK);

        Gtk::Button* login_button = Gtk::manage(new Gtk::Button("Login"));
        login_button->signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_login_clicked));
        box->pack_start(*login_button, Gtk::PACK_SHRINK);

        Gtk::Button* create_account_button = Gtk::manage(new Gtk::Button("Create Account"));
        create_account_button->signal_clicked().connect(sigc::mem_fun(*this, &MyWindow::on_create_account_clicked));
        box->pack_start(*create_account_button, Gtk::PACK_SHRINK);

        show_all_children();
    }

void MyWindow::on_login_clicked() {
    std::string username = username_entry->get_text();
    std::string password = password_entry->get_text();

    if (credentials.authenticateUser(username, password)==0) {
        Gtk::MessageDialog dialog(*this, "Authentication successful!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        dialog.run();
        auto* bWindow = new ButtonWindow();
        bWindow->show();
    } else if(credentials.authenticateUser(username, password)==2) {
        Gtk::MessageDialog dialog(*this, "There is no account associated with that username", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.run();
    } else if(credentials.authenticateUser(username, password)==1) {
        Gtk::MessageDialog dialog(*this, "Wrong Password.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.run();
    } else {
        Gtk::MessageDialog dialog(*this, "Invalid Credentials.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.run();
    }
}

void MyWindow::on_create_account_clicked() {
    std::string username = username_entry->get_text();
    std::string password = password_entry->get_text();

    if (credentials.authenticateUser(username, password)<2) {
        Gtk::MessageDialog dialog(*this, "Username already exists.", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK);
        dialog.run();
    } else {
        credentials.addCredential(username, password);
        Gtk::MessageDialog dialog(*this, "Account created successfully!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        dialog.run();
    }

}

