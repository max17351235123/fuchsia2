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
Napspot ns("1");
int main(int argc, char *argv[]) {


    //vector<string> empty {};
    vector<string> attribute {"sunny", "noisy"};
    //vector<string> attribute2 {"dark", "quiet"};
    //ns.add_napspot("quad", );

    ns.clear_napspots();
    ns.add_napspot("quad", attribute);
    ns.add_reservation("1","5:00");
    ns.add_review("1", "this nap spot rocks", 5);


    //ns.add_napspot("quad1", attribute);
    //ns.add_napspot("quad2", attribute);
    //ns.add_napspot("quad3", attribute);


    //rmb to enclose time in single quotes
    cout << db.double_query("reservations", "user_id", "1", "start_time", "5:00") << " instance" << endl;




    //test code to run usrnme pswd GUI
    /*
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    MyWindow window;
    return app->run(window);
    */


}







