//
// Created by pjsmi on 4/15/2024.
//

#ifndef EXAMPLE_03_USERCREDENTIALS_H
#define EXAMPLE_03_USERCREDENTIALS_H
#include <string>
#include <unordered_map>
#include "Database.h"
#include "Napspot.h"

class UserCredentials {
private:
    Database* db;

public:
    UserCredentials();
    ~UserCredentials();
    void addCredential(const std::string& username, const std::string& password);
    int authenticateUser(const std::string& username, const std::string& password);
    //Napspot* ns;
};


#endif //EXAMPLE_03_USERCREDENTIALS_H
