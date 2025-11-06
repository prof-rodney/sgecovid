#pragma once
#include <string>

using namespace std;

namespace Config
{
    const string DATA_ROOT = "Data";
    const string PACIENTES_DIR = DATA_ROOT + string("/Repository");
    const string RELATORIOS_DIR = DATA_ROOT + string("/Report");
    const string SEGURANCA_DIR = DATA_ROOT + string("/Security");

    const string USERS_FILE = SEGURANCA_DIR + string("/users.txt");
    const string LISTA_COMORBIDADE_FILE = RELATORIOS_DIR + string("/listacomorbidade.txt");

    const string CRYPTO_KEY = "SGECOVID_2025";

    // Interface
    bool ensureDirectories();
} // namespace Config
