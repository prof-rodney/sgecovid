#include "core/Config.h"
#include "core/FileUtils.h"
#include "core/Models.h"
#include "core/Repositories.h"
#include "core/Services.h"
#include "core/UI.h"
#include <iostream>

static void appendComorbidadeRelato(const Patient& p, int idade, bool highRisk) {
    if (!highRisk) return;
    std::string linha = "CEP:" + p.cep + ";Idade:" + std::to_string(idade)
        + ";Comorbidade:" + FileUtils::join(p.comorbidades, ";");
    if (!p.comorbidadesTextoLivre.empty()) linha += ";" + p.comorbidadesTextoLivre;
    FileUtils::appendLine(Config::LISTA_COMORBIDADE_FILE, linha);
}

int main() {
    if (!Config::ensureDirectories()) {
        std::cerr << "Falha ao criar diretorios de dados.\n";
        return 1;
    }
    UserRepository urepo;
    if (!urepo.seedAdminIfEmpty(Config::USERS_FILE, Config::CRYPTO_KEY)) {
        std::cerr << "Falha ao semear admin.\n";
        return 1;
    }

    ConsoleUI ui;
    ui.showWelcome();

    AuthService auth(Config::USERS_FILE, Config::CRYPTO_KEY);
    User current;

    while (true) {
        std::string user, pass;
        if (!ui.promptLogin(user, pass)) continue;
        AuthService::LoginResult res = auth.login(user, pass, current);
        bool userOk = (res != AuthService::LoginResult::InvalidUsername && res != AuthService::LoginResult::InvalidBoth);
        bool passOk = (res != AuthService::LoginResult::InvalidPassword && res != AuthService::LoginResult::InvalidBoth);
        if (res == AuthService::LoginResult::Ok) {
            ui.showLoginFeedback(true, true);
            break;
        } else if (res == AuthService::LoginResult::InvalidUsername) {
            ui.showLoginFeedback(false, true);
        } else if (res == AuthService::LoginResult::InvalidPassword) {
            ui.showLoginFeedback(true, false);
        } else {
            ui.showLoginFeedback(false, false);
        }
    }

    PatientRepository prepo;
    PatientService psvc;
    ComorbidityService csvc;

    while (true) {
        int op = ui.mainMenu(current);
        if (op == 0) {
            std::cout << "Saindo...\n";
            break;
        }
        if (op == 1) {
            Patient p;
            if (ui.inputPatient(p)) {
                for (auto& c : p.comorbidades) c = ComorbidityService::normalize(c);
                if (prepo.save(Config::PACIENTES_DIR, p)) {
                    int idade = psvc.calculaIdade(p.dataNascimento);
                    bool high = csvc.isHighRisk(idade, p.comorbidades);
                    appendComorbidadeRelato(p, idade, high);
                    std::cout << "Paciente salvo com sucesso. Risco alto: " << (high ? "Sim" : "Nao") << "\n";
                } else {
                    std::cout << "Falha ao salvar paciente.\n";
                }
            }
            ui.pause();
        } else if (op == 2) {
            std::string cpf;
            if (ui.promptCpf(cpf)) {
                std::vector<std::string> raw;
                if (!prepo.loadRawByCpf(Config::PACIENTES_DIR, cpf, raw)) {
                    std::cout << "Paciente nao encontrado.\n";
                } else {
                    std::cout << "=== Registro de " << cpf << " ===\n";
                    for (auto& l : raw) std::cout << l << "\n";
                }
            }
            ui.pause();
        } else if (op == 9 && current.role == Role::Admin) {
            std::string u, p;
            Role r = Role::User;
            if (ui.inputNewUser(u, p, r)) {
                if (auth.createUser(u, p, r)) std::cout << "Usuario criado.\n";
                else std::cout << "Falha: username ja existe.\n";
            }
            ui.pause();
        }
    }
    return 0;
}
