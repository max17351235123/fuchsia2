//
// Created by pjsmi on 4/15/2024.
//

#ifndef EXAMPLE_03_USERCREDENTIALS_H
#define EXAMPLE_03_USERCREDENTIALS_H
#include <string>
#include <unordered_map>
#include "Database.h"

class UserCredentials {
private:
    Database* db;

public:
    void addCredential(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
};


#endif //EXAMPLE_03_USERCREDENTIALS_H
