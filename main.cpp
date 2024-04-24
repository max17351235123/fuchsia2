#include <gtkmm.h>
#include <iostream>
#include "Database.h"
#include <sqlite3.h>
#include <vector>
#include "MyWindow.h"
#include <gtkmm/window.h>
#include "Napspot.h"

using namespace std;

Database db("napspots.sqlite", "../database");
UserCredentials uc;
Napspot ns;
int main(int argc, char *argv[]) {




    vector<string> attribute {"sunny", "noisy"};
    vector<string> attribute2 {"dark", "quiet"};
    ns.add_napspot("quad", attribute);


    //test code to run usrnme pswd GUI
    /*
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    MyWindow window;
    return app->run(window);
    */
}







