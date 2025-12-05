#include "Services.h"
#include "Repositories.h"
#include "Config.h"
#include "Crypto.h"
#include "FileUtils.h"
#include <ctime>
#include <cctype>
#include <algorithm>

AuthService::AuthService(const std::string& usersFile, const std::string& key)
: usersFile_(usersFile), key_(key) { }

AuthService::LoginResult AuthService::login(const std::string& username, const std::string& password, User& outUser) {
    UserRepository repo;
    User u;
    bool found = repo.findByUsername(usersFile_, username, u);
    if (!found) {
        return LoginResult::InvalidUsername;
    }
    std::string cipher = Crypto::encrypt(password, key_);
    if (cipher != u.passwordCipher) {
        return LoginResult::InvalidPassword;
    }
    outUser = u;
    return LoginResult::Ok;
}

bool AuthService::createUser(const std::string& username, const std::string& password, Role role) {
    UserRepository repo;
    User existing;
    if (repo.findByUsername(usersFile_, username, existing)) return false;

    User u;
    u.username = username;
    u.role = role;
    u.passwordCipher = Crypto::encrypt(password, key_);
    return repo.addUser(usersFile_, u);
}

static std::string toLowerUnderscore(const std::string& s) {
    std::string out;
    out.reserve(s.size());
    for (unsigned char c : s) {
        if (std::isspace(c)) out.push_back('_');
        else out.push_back(std::tolower(c));
    }
    return out;
}

std::string ComorbidityService::normalize(const std::string& input) {
    return toLowerUnderscore(FileUtils::trim(input));
}

bool ComorbidityService::isValid(const std::string& normalized) {
    return !normalized.empty();
}

bool ComorbidityService::isHighRisk(int idade, const std::vector<std::string>& normalizedList) {
    if (idade >= 65) return true;
    for (auto& c : normalizedList) {
        if (std::find(critical.begin(), critical.end(), c) != critical.end()) return true;
    }
    return false;
}

int PatientService::calculaIdade(const std::string& data) {
    if (data.size() < 10) return 0;
    int ano = std::stoi(data.substr(6,4));
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int anoAtual = now->tm_year + 1900;
    return anoAtual - ano;
}
