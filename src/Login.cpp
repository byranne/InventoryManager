#include "Login.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <cctype>
#include <string>

using namespace std;

int Login::run() {
    int userOption = 0;
    cout << "Enter option 1-2" << endl;
    cout << "1. New User" << endl;
    cout << "2. Existing User" << endl;
    cout << "Enter Here: ";
    cin >> userOption;

    if (userOption == 2) {
        cout << endl;
        return storeExistingUser();
    }

    if (userOption == 1) {
        string userName = storeUsername();
        size_t password = uniquePassChecker();

        ofstream outFS("data//Passwords.txt", ios::app);
        if (!outFS.is_open()) {
            throw runtime_error("Error opening file");
        }
        outFS << userName << ":" << password << "\n";
        outFS.close();
        if(userName == "Admin" ) {
            return 2;
        }
    }

    return 1;
}

size_t Login::passwordHasher(const string& password) {
    hash<string> hasher;
    return hasher(password);
}

size_t Login::uniquePassChecker() {
    string password;
    int uppercase = 0, uniqueChar = 0, numbCount = 0;
    bool perfectPass = false;

    cout << "Please type in password that contains at least 8 chars with at least 2 unique chars (!@#$%^&*?.), 1 uppercase letter and 1 number" << endl;
    cout << "Enter Here: ";
    cin >> password;

    while (!perfectPass) {
        uppercase = uniqueChar = numbCount = 0;

         for(int i = 0; i < password.length(); i++) {
            if(isupper(password.at(i))) {
                uppercase++;
            }
            if(password.at(i) == '!'|| password.at(i) == '@' || password.at(i) == '#' || 
               password.at(i) == '$' || password.at(i) == '%' || password.at(i) == '^' 
               || password.at(i) == '&' || password.at(i) == '*' || password.at(i) == '.' || password.at(i) == '?') {

                uniqueChar++;
            }
            if(isdigit(password.at(i))) {
                numbCount++;
            }
        }

        if (uppercase >= 1 && uniqueChar >= 2 && password.length() >= 8 && numbCount >= 1) {
            perfectPass = true;
        } else {
            system("clear");
            cout << "Invalid password. Try again:\nEnter Here: ";
            cin >> password;
        }
    }

    return passwordHasher(password);
}

string Login::storeUsername() {
    string userName, existingName;
    bool perfectUser = false;

    while (!perfectUser) {
        cout << "Please type a login 5 chars or longer not using :\nEnter Here: ";
        cin >> userName;

        if (userName.length() < 5 || userName.find(':') != string::npos) {
            continue;
        }
        getUserName(userName);
        ifstream infs("data//Passwords.txt");
        if (!infs.is_open()) {
            throw runtime_error("Error opening file");
        }

        bool exists = false;
        while (getline(infs, existingName)) {
            istringstream iss(existingName);
            string existingUser;
            if (getline(iss, existingUser, ':') && existingUser == userName) {
                exists = true;
                break;
            }
        }
        infs.close();

        if (!exists) {
            perfectUser = true;
        } else {
            cout << "Username already exists. Try another.\n";
        }
    }

    return userName;
}

int Login::storeExistingUser() {
    string userNameOne, line;
    bool loginSuccess = false;
    int admin = 0;

    cout << "Please type userName\nEnter Here: ";
    cin >> userNameOne;

    while (!loginSuccess) {
        ifstream infs("data//Passwords.txt");
        if (!infs.is_open()) {
            throw runtime_error("Error opening file");
        }

        bool foundUser = false;
        int maxPassAtmpt = 5;

        while (getline(infs, line)) {
            istringstream iss(line);
            string existingUser, storedHash;
            if (getline(iss, existingUser, ':') && getline(iss, storedHash)) {
                if (existingUser == userNameOne) {
                    getUserName(existingUser);
                    foundUser = true;
                    infs.close();

                    if(existingUser == "Admin") {
                        admin = 2;
                    }

                    while (maxPassAtmpt > 0) {
                        cout << "Type password: ";
                        string passwordInput;
                        cin >> passwordInput;

                        size_t hashedInput = passwordHasher(passwordInput);
                        if (to_string(hashedInput) == storedHash) {
                            cout << "Login successful!\n";
                            loginSuccess = true;
                            if(admin == 2) {
                                return 2;
                            } else {
                                return 1;
                            }
                        } else {
                            maxPassAtmpt--;
                            system("clear");
                            cout << "Incorrect password. " << maxPassAtmpt << " attempts remaining.\n";
                        }

                        if (maxPassAtmpt == 0) {
                            cout << "Reached max attempts. Logging out now.\n";
                            throw runtime_error("Too many failed attempts.");
                        }
                    }
                }
            }
        }
        infs.close();
        int maxAttempt = 5;
        while(maxAttempt > 0) {
            if (!foundUser) {
                cout << "Wrong username. Please try again.\nEnter Here: ";
                cin >> userNameOne;
                cout << "You have " << maxAttempt << " left." << endl;
                maxAttempt--;
            }
        }
        if(maxAttempt == 0) {
            throw runtime_error("Max attempts reached");
        }
    }
    
    if(admin == 2) {
        return 2;
    } else {
        return 1;
    }
}

void Login::getUserName(const string &user) {
    userLogin = user;
}

string Login::userName() {
    return userLogin;
}

