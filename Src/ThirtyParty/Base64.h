#pragma once
#include <string>

using namespace std;

namespace Base64
{
    string encode(const string& in);
    string decode(const string& in);
}