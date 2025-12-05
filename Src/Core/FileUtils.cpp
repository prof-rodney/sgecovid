#include "FileUtils.h"
#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <algorithm>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#include <sys/types.h>
#endif

namespace FileUtils {
    bool ensureDir(const std::string& path) {
    #ifdef _WIN32
        struct _stat info;
        if (_stat(path.c_str(), &info) != 0) {
            return _mkdir(path.c_str()) == 0;
        }
        return (info.st_mode & _S_IFDIR) != 0;
    #else
        struct stat info;
        if (stat(path.c_str(), &info) != 0) {
            return mkdir(path.c_str(), 0755) == 0;
        }
        return S_ISDIR(info.st_mode);
    #endif
    }

    bool fileExists(const std::string& file) {
        std::ifstream f(file);
        return f.good();
    }

    bool readAllLines(const std::string& file, std::vector<std::string>& out) {
        std::ifstream in(file);
        if (!in.is_open()) return false;
        std::string line;
        while (std::getline(in, line)) out.push_back(line);
        return true;
    }

    bool appendLine(const std::string& file, const std::string& line) {
        std::ofstream out(file, std::ios::app);
        if (!out.is_open()) return false;
        out << line << "\n";
        return true;
    }

    bool writeLines(const std::string& file, const std::vector<std::string>& lines) {
        std::ofstream out(file, std::ios::trunc);
        if (!out.is_open()) return false;
        for (auto& l: lines) out << l << "\n";
        return true;
    }

    std::string trim(const std::string& s) {
        auto start = s.find_first_not_of(" \t\r\n");
        if (start == std::string::npos) return "";
        auto end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

    std::vector<std::string> split(const std::string& s, char sep) {
        std::vector<std::string> v;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, sep)) v.push_back(item);
        return v;
    }

    std::string join(const std::vector<std::string>& parts, const std::string& sep) {
        std::ostringstream os;
        for (size_t i=0;i<parts.size();++i) {
            os << parts[i];
            if (i+1 < parts.size()) os << sep;
        }
        return os.str();
    }
}
