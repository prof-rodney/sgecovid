#include "UI.h"
#include <iostream>
#include <limits>

static std::string readLine(const std::string& label) {
    std::cout << label;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static int readInt(const std::string& label, int minV, int maxV) {
    while (true) {
        std::cout << label;
        int x;
        if (std::cin >> x && x >= minV && x <= maxV) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Valor invalido.\n";
    }
}

static bool yesNo(const std::string& label) {
    while (true) {
        std::string s = readLine(label + " (s/n): ");
        if (s == "s" || s == "S") return true;
        if (s == "n" || s == "N") return false;
    }
}

void ConsoleUI::showWelcome() {
    std::cout << "================= SGECOVID =================\n";
}

bool ConsoleUI::promptLogin(std::string& username, std::string& password) {
    username = readLine("Usuario: ");
    password = readLine("Senha: ");
    return !username.empty() && !password.empty();
}

void ConsoleUI::showLoginFeedback(bool userOk, bool passOk) {
    if (userOk && passOk) {
        std::cout << "Login efetuado com sucesso.\n";
        return;
    }
    if (!userOk && !passOk) {
        std::cout << "Usuario e senha invalidos.\n";
    } else if (!userOk) {
        std::cout << "Usuario invalido.\n";
    } else if (!passOk) {
        std::cout << "Senha invalida.\n";
    }
}

int ConsoleUI::mainMenu(const User& user) {
    std::cout << "\n=== Menu Principal (" << (user.role == Role::Admin ? "ADMIN" : "USUARIO") << ") ===\n";
    std::cout << "1) Cadastrar paciente\n";
    std::cout << "2) Consultar paciente por CPF\n";
    if (user.role == Role::Admin) {
        std::cout << "9) [ADMIN] Cadastrar novo usuario\n";
    }
    std::cout << "0) Sair\n";
    return readInt("Escolha: ", 0, 9);
}

void ConsoleUI::pause() {
    std::cout << "Pressione ENTER para continuar...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool ConsoleUI::inputPatient(Patient& p) {
    std::cout << "\n== Cadastro de Paciente ==\n";
    p.nome = readLine("Nome: ");
    p.cpf = readLine("CPF (somente numeros): ");
    p.endereco = readLine("Endereco: ");
    p.cidade = readLine("Cidade: ");
    p.bairro = readLine("Bairro: ");
    p.cep = readLine("CEP (somente numeros): ");
    p.dataNascimento = readLine("Data Nascimento (dd/mm/aaaa): ");
    p.dataDiagnostico = readLine("Data Diagnostico (dd/mm/aaaa): ");
    p.email = readLine("Email: ");

    if (yesNo("Possui comorbidades?")) {
        std::cout << "Informe comorbidades, separadas por ';' (ex: diabetes;doenca_cardiaca)\n";
        std::string c = readLine("Comorbidades: ");
        size_t start = 0;
        while (true) {
            size_t pos = c.find(';', start);
            std::string item = (pos == std::string::npos) ? c.substr(start) : c.substr(start, pos - start);
            if (!item.empty()) p.comorbidades.push_back(item);
            if (pos == std::string::npos) break;
            start = pos + 1;
        }
        if (yesNo("Deseja adicionar texto livre de comorbidades?")) {
            p.comorbidadesTextoLivre = readLine("Texto livre: ");
        }
    }
    return true;
}

bool ConsoleUI::inputNewUser(std::string& username, std::string& password, Role& role) {
    std::cout << "\n== Novo Usuario ==\n";
    username = readLine("Username: ");
    password = readLine("Senha: ");
    int r = readInt("Role (1=User, 2=Admin): ", 1, 2);
    role = (r == 2) ? Role::Admin : Role::User;
    return !username.empty() && !password.empty();
}

bool ConsoleUI::promptCpf(std::string& cpf) {
    cpf = readLine("Informe o CPF: ");
    return !cpf.empty();
}
