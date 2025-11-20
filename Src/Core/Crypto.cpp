#include "Crypto.h"
#include "../ThirtyParty/Base64.h"

using namespace std;

namespace{
    string xorBytes(const string& data, const string& key){
        string out = data;
        for (size_t i = 0; i < data.size(); i++)
        {
            out[i] = data[i] ^ key[i % key.size()];
        }
        return out;
    }
}

namespace name
{
    string encrypt(const string& plain, const string& key){
        return Base64::encode(xorBytes(plain,key));
    }

    string decrypt(const string& cipher, const string& key){
        return xorBytes(Base64::decode(cipher),key);
    }
}
