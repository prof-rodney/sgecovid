#include "Crypto.h"
#include "../thirdparty/Base64.h"

namespace {
    std::string xorBytes(const std::string& data, const std::string& key) {
        std::string out = data;
        for (size_t i=0;i<data.size();++i) {
            out[i] = data[i] ^ key[i % key.size()];
        }
        return out;
    }
}

namespace Crypto {
    std::string encrypt(const std::string& plain, const std::string& key) {
        return Base64::encode(xorBytes(plain, key));
    }
    std::string decrypt(const std::string& cipher, const std::string& key) {
        return xorBytes(Base64::decode(cipher), key);
    }
}
