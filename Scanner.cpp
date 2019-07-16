#include <utility>

//============================================================================
// @name        : Scanner.cpp
// @author      : Ward Gauderis
// @date        : 7/7/19
// @version     : 
// @copyright   : BA1 Informatica - Ward Gauderis - University of Antwerp
// @description : 
//============================================================================
#include "Scanner.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <array>

std::ostream &operator<<(std::ostream &out, const Type type) {
    std::string s;
    switch (type) {
        case Type::U:
            s = "#FF9000";
            break;
        case Type::H:
            s = "#E33B3B";
            break;
        case Type::C:
            s = "#3BB33B";
            break;
        case Type::L:
            s = "#505050";
            break;
    }
    return out << s;
}

File::File(path p, Type t) : absPath(std::move(p)), type(t) {}

Scanner::Scanner(bool u, bool h, bool c, bool l, bool r, const path &path) :
        U(u), H(h), C(c), L(l), recursive(r) {
    if (is_directory(path)) {
        workingDir = path;
        current_path(workingDir);
        scanFolder(path);
    } else {
        workingDir = path.parent_path();
        current_path(workingDir);
        scanFile(path);
    }
}

void Scanner::scanFolder(const path &path) {
    for (const auto &entry: directory_iterator(path)) {
        if (entry.is_directory()) {
            if (entry.path().filename() == "cmake-build-debug" || entry.path().filename() == "CMakeFiles" || entry.path().filename() == "backup") continue;
            scanFolder(entry.path());
        } else {
            scanFile(entry.path());
        }
    }
}

void Scanner::scanFile(const path &path) {
    Type temp;
    if (hExtensions.find(path.extension()) != hExtensions.end()) {
        temp = Type::H;
    } else if (cExtensions.find(path.extension()) != cExtensions.end()) {
        temp = Type::C;
    } else return;

    size_t index;
    if (check.find(path) != check.end()) {
        if (files[check[path]].type != Type::U) return;
        else index = check[path];
    } else {
        index = files.size();
        files.emplace_back(path, Type::U);
        check[path] = index;

        adjacencyMatrix.emplace_back(std::vector<bool>(index, false));
        for (auto &i: adjacencyMatrix) {
            i.emplace_back(false);
        }
    }

    std::ifstream iFile(path);
    if (!iFile.good()) {
        return;
    }

    files[index].type = temp;

    const std::string p = path.parent_path().string();  //if no string is used, a bad malloc occurs when assigning the current_path() for some reason

    std::string line;
    while (getline(iFile, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        if (line.size() < 8) continue;
        if (line.substr(0, 8) != "#include") continue;

        Type type;
        switch (line[8]) {
            case '"':
                type = Type::U;
                break;
            case '<':
                type = Type::L;
                break;
            default:
                continue;
        }

        long unsigned int end = line.find_first_of(type == Type::L ? '>' : '"', 9);
        if (end == std::string::npos) continue;

        std::string included = line.substr(9, end - 9);

        class path abs;
        if (type == Type::L) {
            abs = absolute(included);
        } else {
            current_path(p);
            try {
                abs = canonical(included);
            } catch (...) {
                abs = absolute(included);
            }
            current_path(workingDir);
        }

        size_t index1;
        if (check.find(abs) != check.end()) {
            index1 = check[abs];
        } else {
            index1 = files.size();
            files.emplace_back(abs, type);
            check[abs] = index1;

            adjacencyMatrix.emplace_back(std::vector<bool>(index1, false));
            for (auto &i: adjacencyMatrix) {
                i.emplace_back(false);
            }
        }

        adjacencyMatrix[index][index1] = true;
    }

    if (!recursive) return;

    for (size_t i = 0; i < files.size(); ++i) {
        if (adjacencyMatrix[index][i]) {
            scanFile(files[i].absPath);
        }
    }
}

void Scanner::print() const {
    std::vector<bool> toPrint(files.size(), false);
    for (size_t i = 0; i < files.size(); ++i) {
        toPrint[i] = print(files[i].type);
    }

    if (!H || !C) {
        for (size_t i = 0; i < files.size(); ++i) {
            if (!toPrint[i]) continue;
            if (files[i].type == Type::H || files[i].type == Type::C) continue;
            toPrint[i] = false;
            for (size_t j = 0; j < files.size(); ++j) {
                if (!adjacencyMatrix[j][i]) continue;
                if (toPrint[j]) {
                    toPrint[i] = true;
                    break;
                }
            }
        }
    }

    std::string dotName = temp_directory_path() / "includes.dot";
    std::string pngName = temp_directory_path() / "includes.png";
    std::ofstream oFile(dotName);
    if (!oFile.good()) return;

    oFile << "digraph includes{\n"
             "\tbgcolor=\"#252525\";\n"
             "\toutputorder=edgesfirst;\n"
             "\tresolution=250;\n\n"
             "\tnode [ color=\"#252525\", fontcolor=white, height=0.5, width=0.75, fontname=roboto, shape=box, style=filled ];\n"
             "\tedge [ penwidt=2.5 ];\n\n";

    for (size_t i = 0; i < files.size(); ++i) {
        if (!toPrint[i]) continue;

        oFile << "\t\"" << i << "\" [ fillcolor=\"" << files[i].type << "\", label=" << relative(files[i].absPath)
              << "];\n";
    }

    oFile << "\n";

    for (size_t i = 0; i < files.size(); ++i) {
        if (!toPrint[i]) continue;

        for (size_t j = 0; j < files.size(); ++j) {
            if (!toPrint[j]) continue;
            if (!adjacencyMatrix[i][j]) continue;

            oFile << "\t\"" << i << "\" -> \"" << j << "\" [ color =\"" << files[j].type
                  << "\", dir=back ];\n";
        }
    }

    oFile << "\n\t{ rank=same; ";
    for (size_t i = 0; i < files.size(); ++i) {
        if (files[i].type != Type::L) continue;
        if (!toPrint[i]) continue;
        oFile << "\"" << i << "\" ";
    }
    oFile << "};\n";


    oFile << "}";

    std::string command =
            "(dot -Tpng " + dotName + " -o " + pngName + " && xdg-open " + pngName + ") >/dev/null 2>&1 &";
    system(command.c_str());
}

bool Scanner::print(Type type) const {
    switch (type) {
        case Type::U:
            return U;
        case Type::H:
            return H;
        case Type::C:
            return C;
        case Type::L:
            return L;
    }
    return true;
}

void Scanner::transitiveReduction(bool apply) {
    // Warshall's Algorithm for transitive closure
    auto R1 = adjacencyMatrix;
    auto backup = adjacencyMatrix;
    for (size_t k = 0; k < files.size(); ++k) {
        for (size_t i = 0; i < files.size(); ++i) {
            for (size_t j = 0; j < files.size(); ++j) {
                R1[i][j] = adjacencyMatrix[i][j] || (adjacencyMatrix[i][k] && adjacencyMatrix[k][j]);
            }
        }
        std::swap(adjacencyMatrix, R1);
    }

    // Hsu's Algorithm for reflexive and transitive reduction
    for (size_t i = 0; i < files.size(); ++i) adjacencyMatrix[i][i] = false;

    for (size_t j = 0; j < files.size(); ++j) {
        for (size_t i = 0; i < files.size(); ++i)
            if (adjacencyMatrix[i][j])
                for (size_t k = 0; k < files.size(); ++k)
                    if (adjacencyMatrix[j][k])
                        adjacencyMatrix[i][k] = false;
    }

    if(!apply) return;

    for (size_t i = 0; i < files.size(); ++i) {
        for (size_t j = 0; j < files.size(); ++j) {
            if (!adjacencyMatrix[i][j] && backup[i][j]) {
                removeInclude(files[i], files[j]);
            }
        }
    }
}

void Scanner::removeInclude(const File &file, const File &include) const {
    std::ifstream iFile(file.absPath);
    path out = file.absPath.parent_path() / (file.absPath.filename().string() + ".new");
    std::ofstream oFile(out);

    if (!iFile.good() || !oFile.good()) {
        return;
    }

    std::string remove = "#include";
    if (include.type == Type::L) {
        remove = remove + "<" + include.absPath.filename().string() + ">";
    } else {
        remove = remove + "\"" + relative(include.absPath, file.absPath.parent_path()).string() + "\"";
    }

    bool found = false;

    std::string line;
    std::string backup;
    while (getline(iFile, line)) {
        backup = line;
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        if (line.size() < remove.size() || line.substr(0, remove.size()) != remove) {
            oFile << backup << std::endl;
            continue;
        }

        found = true;
    }

    if (!found) throw std::runtime_error("Not found: " + file.absPath.string() + " -> " + remove);

    oFile.close();
    iFile.close();

    create_directories(("backup" / relative(file.absPath, workingDir).parent_path()));
    rename(file.absPath, "backup"/relative(file.absPath, workingDir));
    rename(out, file.absPath);
}
