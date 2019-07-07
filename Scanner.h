//============================================================================
// @name        : Scanner.h
// @author      : Ward Gauderis
// @date        : 7/7/19
// @version     : 
// @copyright   : BA1 Informatica - Ward Gauderis - University of Antwerp
// @description : 
//============================================================================
#ifndef TODOT_SCANNER_H
#define TODOT_SCANNER_H

#include <set>
#include <map>
#include <filesystem>

using namespace std::filesystem;

struct File {
    std::set<std::pair<std::string, bool>> includes;
    bool implementation;
};

class Scanner {
    const std::set<std::string> cExtensions = {".c", ".cpp", ".cc", ".C", ".cxx", ".c++"};
    const std::set<std::string> hExtensions = {".h", ".hpp", ".hh", ".H", ".hxx", ".h++"};

    std::map<std::string, File> files;

    bool header;

    void scanFolder(const path &path);

    void scanFile(const path &path);

    void print();

public:
    explicit Scanner(bool header);
};


#endif //TODOT_SCANNER_H
