#include <gtkmm.h>
#include <iostream>
#include "Database.h"
#include <sqlite3.h>
#include <vector>
#include "MyWindow.h"
#include <gtkmm/window.h>
#include "Napspot.h"
#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>


using namespace std;

Database db("napspots.sqlite", "../database");
UserCredentials uc;
Napspot ns("1");

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/treeview.h>
#include <gtkmm/liststore.h>
#include <sqlite3.h>
#include <glibmm/value.h>

int main(int argc, char *argv[]) {


    //vector<string> empty {};
    vector<string> attribute {"sunny", "noisy"};
    vector<string> attribute2 {"dark", "noisy"};

    //vector<string> attribute2 {"dark", "quiet"};
    //ns.add_napspot("quad", );

    ns.clear_napspots();
    ns.add_napspot("quad", attribute);
    ns.add_napspot("quad2", attribute2);
    ns.add_napspot("quad3", attribute2);
    ns.add_napspot("quad4", attribute);
    ns.add_napspot("quad5", attribute2);

    ns.add_reservation("1","5:00");
    ns.add_review("1", "this nap spot rocks", 5);
    ns.filter_by_attribute("sunny");

}