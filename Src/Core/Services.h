#pragma once
#include "Models.h"
#include <string>
#include <vector>

class AuthService {
public:
    AuthService(const std::string& usersFile, const std::string& cryptoKey);

    enum class LoginResult { Ok, InvalidUsername, InvalidPassword, InvalidBoth };

    LoginResult login(const std::string& username, const std::string& password, User& outUser);
    bool createUser(const std::string& username, const std::string& password, Role role);

private:
    std::string usersFile_;
    std::string key_;
};

class ComorbidityService {
public:
    const std::vector<std::string> baseList = {
        "diabetes", "hipertensao", "doenca_cardiaca", "doenca_respiratoria",
        "obesidade_grau3", "imunossuprimido", "doenca_renal", "cancer"
    };

    const std::vector<std::string> critical = {
        "diabetes", "doenca_cardiaca", "doenca_respiratoria",
        "obesidade_grau3", "imunossuprimido"
    };

    static std::string normalize(const std::string& input);
    bool isValid(const std::string& normalized);
    bool isHighRisk(int idade, const std::vector<std::string>& normalizedList);
};

class PatientService {
public:
    int calculaIdade(const std::string& dataNascimento);
};
