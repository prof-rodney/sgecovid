#pragma once
#include "Models.h"
#include <string>
#include <vector>

class UserRepository {
public:
    bool seedAdminIfEmpty(const std::string& usersFile, const std::string& cryptoKey);
    bool findByUsername(const std::string& usersFile, const std::string& username, User& outUser);
    bool addUser(const std::string& usersFile, const User& user);
};

class PatientRepository {
public:
    bool save(const std::string& pacientesDir, const Patient& p);
    bool loadRawByCpf(const std::string& pacientesDir, const std::string& cpf,
                      std::vector<std::string>& outLines);
};
