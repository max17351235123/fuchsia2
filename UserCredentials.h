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
    /**
     * Constructor that initalizes db being used
     */
    UserCredentials();
    /**
     * Empty Destructor
     */
    ~UserCredentials();
    /**
     * Adds new account to users table & logs to users.csv
     * @param username
     * @param password
     */
    void addCredential(const std::string& username, const std::string& password);
    /**
     * Checks if username or password inputted belong to a valid account
     * @param username
     * @param password
     * @return 3 different ints depending on error:incorrect username, incorrect password, correct
     */
    int authenticateUser(const std::string& username, const std::string& password);
};


#endif //EXAMPLE_03_USERCREDENTIALS_H
