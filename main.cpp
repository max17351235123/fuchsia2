#include <gtkmm.h>
#include <iostream>
#include "Database.h"
#include <sqlite3.h>
#include <vector>
#include "MyWindow.h"
#include <gtkmm/window.h>
using namespace std;

Database db("napspots.sqlite", "../database");
UserCredentials uc;

int main(int argc, char *argv[]) {
    //a
   //vector<string> tab1col = {"location_id", "name", "attribute", "reservation"};
   //vector<string> tab1val = {"7", "lafayette_college", "sunny", "false"};

    //db.add_row(db.get_curr(), "locations", tab1col, tab1val);
    //cout << db.query("locations", "location_id", "5","name");
   // uc.addCredential("max_votaw2","password1");
    //uc.addCredential("max_votaw2","password1");
    //cout << uc.authenticateUser("max_votaw", "password1") << endl;
    //cout << uc.authenticateUser("max_votax", "password1") << endl;


    //test code to run usrnme pswd GUI

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    MyWindow window;
    return app->run(window);

}







