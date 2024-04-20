//
// Created by pjsmi on 4/15/2024.
//

#include "UserCredentials.h"
#include <iostream>
#include <vector>
#include <sqlite3.h>
#include "Database.h"
using namespace std;

UserCredentials::UserCredentials() {
    db = Database::get_db("napspots.sqlite", "../database");
}
UserCredentials::~UserCredentials(){
}

void UserCredentials::addCredential(const string& user_id, const std::string& username, const std::string& password) {
    vector<string> tab1col = {"user_id", "username", "password"};
    vector<string> newAccount = {"1", username, password};
    db->add_row(db->get_curr(), "users", tab1col, newAccount);
    string file = db->get_location() + "/csv/users.csv";
    cout << file << endl;
    db->log_to_csv("users", file);
}

bool UserCredentials::authenticateUser(const std::string& username, const std::string& password) {
    cout << username << endl;
    string output = db->query("users", "password", "username", username); // outputs the password
    cout << output;

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



