#pragma once
#include "Models.h"
#include <string>

class ConsoleUI {
public:
    void showWelcome();
    bool promptLogin(std::string& username, std::string& password);
    void showLoginFeedback(bool userOk, bool passOk);

    int mainMenu(const User& user);
    void pause();

    bool inputPatient(Patient& p);
    bool inputNewUser(std::string& username, std::string& password, Role& role);
    bool promptCpf(std::string& cpf);
};
