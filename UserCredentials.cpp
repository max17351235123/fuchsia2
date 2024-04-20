//
// Created by pjsmi on 4/15/2024.
//

#include "UserCredentials.h"
#include <iostream>
#include <vector>
#include <sqlite3.h>
#include "Database.h"
using namespace std;

void UserCredentials::addCredential(const std::string& username, const std::string& password) {
    //vector<string> tab1col = {"location_id", "username", "attribute", "reservation"};
   // vector<string> newAccount = {"1", "lafayette_college", "sunny", "false"};

   // db.add_row(db.get_curr(), "locations", tab1col, tab1val);

}
bool UserCredentials::authenticateUser(const std::string& username, const std::string& password) {

    string output = db->query("users", "password", username,"password"); // outputs the password

    if(output == password){
        return true;
    }
    if (output != password) {
        cerr << "The password doesn't seem to match the username" << endl;
        return false;
    }
    if (output == " ") {
        cerr << "There is no account associated with that username" << endl;
        return false;
    }
    return false;

}



