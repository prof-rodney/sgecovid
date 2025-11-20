#pragma once
#include <string>

using namespace std;

namespace name
{
    string encrypt(const string& plain, const string& key);
    string decrypt(const string& cipher, const string& key);
}
