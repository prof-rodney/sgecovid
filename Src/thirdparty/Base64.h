#pragma once
#include <string>
namespace Base64 {
    std::string encode(const std::string& in);
    std::string decode(const std::string& in);
}
