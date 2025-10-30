#pragma once
#include <string>
#include <vector>

using namespace std;

enum class Role { User, Admin};

struct User
{
    string username;
    string passwordCipher;
    Role role;
};

struct Patient
{
    string nome;
    string cpf;
    string endereco;
    string cidade;
    string bairro;
    string cep;
    string dataNascimento; 
    string dataDiagnostico;
    string email;
    vector<string> comorbidades;
    string comorbidadesTextoLivre;
};
