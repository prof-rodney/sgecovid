#pragma once
#include <string>
namespace Crypto {
    std::string encrypt(const std::string& plain, const std::string& key);
    std::string decrypt(const std::string& cipher, const std::string& key);
}
