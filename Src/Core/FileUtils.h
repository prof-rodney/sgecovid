#pragma once
#include <string>
#include <vector>

namespace FileUtils {
    bool ensureDir(const std::string& path);
    bool readAllLines(const std::string& file, std::vector<std::string>& out);
    bool appendLine(const std::string& file, const std::string& line);
    bool writeLines(const std::string& file, const std::vector<std::string>& lines);
    bool fileExists(const std::string& file);

    std::string trim(const std::string& s);
    std::vector<std::string> split(const std::string& s, char sep);
    std::string join(const std::vector<std::string>& parts, const std::string& sep);
}
