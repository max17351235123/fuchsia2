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

void UserCredentials::addCredential(const std::string& username, const std::string& password) {

    //add 1 to the biggest ccurrent user_id
    int user_id = db->id_query("users", "user_id") + 1;

    //add a new account
    vector<string> usertable = {"user_id", "username", "password"};
    vector<string> newAccount = {to_string(user_id), username, password};

    int auth = authenticateUser(username, password);
    if (auth != 2) {
        cerr << "account with that name already exists" << endl;
        return;
    }

    db->add_row("users", usertable, newAccount);

    //log it to the csv
    string file = db->get_location() + "/csv/users.csv";
    db->log_to_csv("users", file);
}

int UserCredentials::authenticateUser(const string& username, const string& password) {
    string output = db->query("users", "password", "username", username);
    if(output == password){
        return 0;
    }
    if (output.empty()) {
        cerr << "There is no account associated with that username" << endl;
        return 2;
    }
    if (output != password) {
        cerr << "The password doesn't seem to match the username" << endl;
        return 1;
    }
    return 3;
}



