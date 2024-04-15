#include <gtkmm.h>
#include <iostream>
#include "Database.h"
#include <sqlite3.h>
#include <vector>
using namespace std;

Database db("napspots.sqlite", "../database");

int main(int argc, char *argv[]) {

   vector<string> tab1col = {"location_id", "name", "attribute", "reservation"};
   vector<string> tab1val = {"5", "lafayette_college", "sunny", "false"};

    db.add_row(db.get_curr(), "locations", tab1col, tab1val);

     sqlite3_exec(db.get_curr(), sql.c_str(), nullptr, nullptr, &db.zErrMsg);

}







