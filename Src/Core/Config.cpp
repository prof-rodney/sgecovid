#include "Config.h"
#include "FileUtils.h"

namespace Config {
    const std::string DATA_ROOT = "data";
    const std::string PACIENTES_DIR = DATA_ROOT + std::string("/pacientes");
    const std::string RELATORIOS_DIR = DATA_ROOT + std::string("/relatorios");
    const std::string SEGURANCA_DIR = DATA_ROOT + std::string("/seguranca");

    const std::string USERS_FILE = SEGURANCA_DIR + std::string("/users.txt");
    const std::string LISTA_COMORBIDADE_FILE = RELATORIOS_DIR + std::string("/listaComorbidade.txt");

    const std::string CRYPTO_KEY = "SNCOVID_KEY_2025";

    bool ensureDirectories() {
        bool ok = true;
        ok &= FileUtils::ensureDir(DATA_ROOT);
        ok &= FileUtils::ensureDir(PACIENTES_DIR);
        ok &= FileUtils::ensureDir(RELATORIOS_DIR);
        ok &= FileUtils::ensureDir(SEGURANCA_DIR);
        return ok;
    }
}
