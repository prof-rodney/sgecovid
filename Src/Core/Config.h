#pragma once
#include <string>

namespace Config {
    extern const std::string DATA_ROOT;
    extern const std::string PACIENTES_DIR;
    extern const std::string RELATORIOS_DIR;
    extern const std::string SEGURANCA_DIR;

    extern const std::string USERS_FILE;
    extern const std::string LISTA_COMORBIDADE_FILE;

    extern const std::string CRYPTO_KEY;

    bool ensureDirectories();
}
