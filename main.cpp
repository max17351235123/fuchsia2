#include <gtkmm.h>
#include <iostream>
#include "Database.h"
#include <sqlite3.h>
#include <vector>
#include "AppForum.h"
using namespace std;

Database db("napspots.sqlite", "../database");

int main(int argc, char *argv[]) {
    //a
   vector<string> tab1col = {"location_id", "name", "attribute", "reservation"};
   vector<string> tab1val = {"5", "lafayette_college", "sunny", "false"};

    db.add_row(db.get_curr(), "locations", tab1col, tab1val);

    auto app =
            Gtk::Application::create(argc, argv, "edu.cs205.example03");

    Gtk::Window window;
    window.set_title("App Forum");
    window.set_default_size(600, 400);

    // Create the AppForum instance and add it to the window
    AppForum app_forum;
    window.add(app_forum);

    // Show the window and run the application
    window.show_all();
    return app->run(window);
}







