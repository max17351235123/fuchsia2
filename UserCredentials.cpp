//
// Created by pjsmi on 4/15/2024.
//

#include "UserCredentials.h"
void UserCredentials::addCredential(const std::string& username, const std::string& password) {
    credentials[username] = password;
}
bool UserCredentials::authenticateUser(const std::string& username, const std::string& password) {

    //string output = query("users", "username", username): outputs the password

    auto it = credentials.find(username);
    if (it != credentials.end() && it->second == password) {
        return true;
    }
    return false;
}

void UserCredentials::removeCredential(const std::string& username) {
    credentials.erase(username);
}

size_t UserCredentials::getNumCredentials() const {
    return credentials.size();
}

