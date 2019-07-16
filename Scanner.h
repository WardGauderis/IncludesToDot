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

#include <filesystem>
#include <set>
#include <map>
#include <vector>

using namespace std::filesystem;

enum class Type {
    U, H, C, L
};

std::ostream &operator<<(std::ostream &out, Type type);

struct File {
    const path absPath;
    Type type;

    File(path absPath, Type type);
};

class Scanner {
    const std::set<std::string> cExtensions = {".c", ".cpp", ".cc", ".C", ".cxx", ".c++"};
    const std::set<std::string> hExtensions = {".h", ".hpp", ".hh", ".H", ".hxx", ".h++"};

    std::map<path, size_t> check;
    std::vector<File> files;
    std::vector<std::vector<bool>> adjacencyMatrix;

    bool U;
    bool H;
    bool C;
    bool L;
    bool recursive;

    path workingDir;

    void scanFolder(const path &path);

    void scanFile(const path &path);

    bool print(Type type) const;

    void removeInclude(const File &file, const File &include) const;

public:
    Scanner(bool u, bool h, bool c, bool l, bool r, const path &path);

    void print(const std::string& filename) const;

    void transitiveReduction(bool apply);
};

#endif //TODOT_SCANNER_H
