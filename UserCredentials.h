//
// Created by pjsmi on 4/15/2024.
//

#ifndef EXAMPLE_03_USERCREDENTIALS_H
#define EXAMPLE_03_USERCREDENTIALS_H
#include <string>
#include <unordered_map>

class UserCredentials {
private:
    std::unordered_map<std::string, std::string> credentials;

public:
    void addCredential(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);
    void removeCredential(const std::string& username);
    size_t getNumCredentials() const;
};


#endif //EXAMPLE_03_USERCREDENTIALS_H
