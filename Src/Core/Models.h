#pragma once
#include <string>
#include <vector>

enum class Role { User, Admin };

struct User {
    std::string username;
    Role role;
    std::string passwordCipher;
};

struct Patient {
    std::string nome;
    std::string cpf;
    std::string endereco;
    std::string cidade;
    std::string bairro;
    std::string cep;
    std::string dataNascimento;
    std::string dataDiagnostico;
    std::string email;
    std::vector<std::string> comorbidades;
    std::string comorbidadesTextoLivre;
};
