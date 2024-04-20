//
// Created by pjsmi on 4/15/2024.
//

#include "UserCredentials.h"
#include <iostream>
using namespace std;
void UserCredentials::addCredential(const std::string& username, const std::string& password) {
    credentials[username] = password;
}
bool UserCredentials::authenticateUser(const std::string& username, const std::string& password) {

    //string output = query("users", "username", username): outputs the password
    string output = " ";
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
}

void UserCredentials::removeCredential(const std::string& username) {
    credentials.erase(username);
}

size_t UserCredentials::getNumCredentials() const {
    return credentials.size();
}

