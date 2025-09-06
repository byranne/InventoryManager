#ifndef LOGIN_H
#define LOGIN_H

#include <string>

using namespace std;

class Login {
public:
    int run(); // Entry point for main
    string userName(); // returns current logged-in user name
    void getUserName(const string &user); // set userLogin
private:
    string userLogin;

    // Internal helper methods
    size_t passwordHasher(const std::string& password); // Hashs a password
    size_t uniquePassChecker(); // Validates and hashs a password 
    std::string storeUsername(); // Gets good user name
    int storeExistingUser(); // Handles exisitng user
};

#endif
