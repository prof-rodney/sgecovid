#include "Repositories.h"
#include "FileUtils.h"
#include "Config.h"
#include "Crypto.h"
#include <sstream>

using namespace std;

static std::string roleToStr(Role r) {
    return r == Role::Admin ? "admin" : "user";
}

static Role strToRole(const std::string& s) {
    return (s == "admin") ? Role::Admin : Role::User;
}

bool UserRepository::seedAdminIfEmpty(const std::string& usersFile, const std::string& key) {
    if (!FileUtils::fileExists(usersFile)) {
        std::vector<std::string> lines;
        std::string pass = Crypto::encrypt("admin123", key);
        lines.push_back("admin|admin|" + pass);
        return FileUtils::writeLines(usersFile, lines);
    }

    std::vector<std::string> lines;
    FileUtils::readAllLines(usersFile, lines);
    if (lines.empty()) {
        std::string pass = Crypto::encrypt("admin123", key);
        lines.push_back("admin|admin|" + pass);
        return FileUtils::writeLines(usersFile, lines);
    }
    return true;
}

bool UserRepository::findByUsername(const std::string& usersFile, const std::string& username, User& outUser) {
    std::vector<std::string> lines;
    if (!FileUtils::readAllLines(usersFile, lines))
        return false;

    for (auto& l : lines) {
        auto parts = FileUtils::split(FileUtils::trim(l), '|');
        if (parts.size() != 3) continue;
        if (parts[0] == username) {
            outUser.username = parts[0];
            outUser.role = strToRole(parts[1]);
            outUser.passwordCipher = parts[2];
            return true;
        }
    }
    return false;
}

bool PatientRepository::loadRawByCpf(const std::string& dir, const std::string& cpf,
                                     std::vector<std::string>& outLines) {
    const std::string path = dir + "/" + cpf + ".txt";
    outLines.clear();
    return FileUtils::readAllLines(path, outLines);
}

bool UserRepository::addUser(const std::string& usersFile, const User& user) {
    std::string line = user.username + "|" + roleToStr(user.role) + "|" + user.passwordCipher;
    return FileUtils::appendLine(usersFile, line);
}

bool PatientRepository::save(const std::string& dir, const Patient& p) {
    std::vector<std::string> lines;
    lines.push_back("Nome: " + p.nome);
    lines.push_back("CPF: " + p.cpf);
    lines.push_back("Endereco: " + p.endereco);
    lines.push_back("Cidade: " + p.cidade);
    lines.push_back("Bairro: " + p.bairro);
    lines.push_back("CEP: " + p.cep);
    lines.push_back("DataNascimento: " + p.dataNascimento);
    lines.push_back("DataDiagnostico: " + p.dataDiagnostico);
    lines.push_back("Email: " + p.email);
    lines.push_back("Comorbidades: " + FileUtils::join(p.comorbidades, ";"));
    if (!p.comorbidadesTextoLivre.empty())
        lines.push_back("ComorbidadesTextoLivre: " + p.comorbidadesTextoLivre);

    const std::string path = dir + "/" + p.cpf + ".txt";
    return FileUtils::writeLines(path, lines);
}
