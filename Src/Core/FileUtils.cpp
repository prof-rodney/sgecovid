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

using namespace std;

namespace FileUtils{
    
    bool ensureDir(const string& path){
        #ifdef _WIN32
            struct _stat info;
            if (_stat(path.c_str(), &info) != 0)
            {
                return _mkdir(path.c_str()) == 0;
            }
            return (info.st_mode & _S_IFDIR) != 0;
        #else
            struct stat info;
            if (stat(path.c_str(), &info) != 0)
            {
                return mkdir(path.c_str(), 0755) == 0;
            }
            return S_ISDIR(info.st_mode);
        #endif
            
    }

    bool fileExists(const string& file){
        ifstream f(file);
        return f.good();
    }

    bool readAlllines(const string& file, vector<string>& out){
        ifstream in(file);

        if(!in.is_open()) return false;

        string line;

        while(getline(in, line)) out.push_back(line);

        return true;
    }

    bool appendLine(const string& file, const string& line){
        ofstream out(file, ios::app);
        if(!out.is_open()) return false;
        
        out << line << "\n";
        return true;
    }

    bool writeLines(const string& file, const vector<string>& lines){
        ofstream out(file, ios::trunc);
        if(!out.is_open()) return false;
        
        for(auto& l: lines) out << l << "\n";
        return true;
    }

    string trim(const string& s){
        auto start = s.find_first_not_of(" \t\r\n");
        if (start == string::npos)
        {
            return "";
        }

        auto end = s.find_last_not_of(" \t\r\n");
        return s.substr(start, end - start + 1);
    }

    string join(const vector<string>& parts, const string& sep){
        ostringstream os;
        for (size_t i = 0; i < parts.size(); i++)
        {
            os << parts[i];
            if(i+1 < parts.size())
                os << sep;
        }

        return os.str();
    }

    vector<string> split(const string& s, char sep){
        vector<string> vet;
        stringstream ss(s);
        string elemento;
        while (getline(ss, elemento, sep))
        {
            vet.push_back(elemento);
        }
        return vet;
    }
}