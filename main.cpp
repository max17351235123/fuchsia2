#include <gtkmm.h>
#include <iostream>
#include "Database.h"
#include <sqlite3.h>
#include <vector>
using namespace std;

Database db("napspots.sqlite", "../database");

int main(int argc, char *argv[]) {

   vector<string> table1Columns = {"location_id", "name", "attribute", "reservation"};
   vector<string> table1Values = {"4", "lafayette_college", "sunny", "false"};

    db.add_row(db.get_curr(), "locations", table1Columns, table1Values);
}