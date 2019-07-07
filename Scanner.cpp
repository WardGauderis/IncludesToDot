//============================================================================
// @name        : Scanner.cpp
// @author      : Ward Gauderis
// @date        : 7/7/19
// @version     : 
// @copyright   : BA1 Informatica - Ward Gauderis - University of Antwerp
// @description : 
//============================================================================
#include <fstream>
#include <algorithm>
#include <iostream>
#include "Scanner.h"

void Scanner::scanFolder(const path &path) {
    directory_iterator iterator(path);
    for (const auto &entry: iterator) {
        if (entry.is_directory()) {
            if (entry.path().filename() == "cmake-build-debug" || entry.path().filename() == "CMakeFiles") continue;
            scanFolder(entry.path());
        } else {    //files not included
            if (files.find(relative(entry)) == files.end()) scanFile(entry.path());
        }
    }
}

void Scanner::scanFile(const path &path) {
    File file;

    if (hExtensions.find(path.extension()) != hExtensions.end()) {
        file.implementation = false;
    } else if (!header && cExtensions.find(path.extension()) != cExtensions.end()) {    //headers only
        file.implementation = true;
    } else return;

    std::ifstream iFile(path);
    if (!iFile.good()) return;

    std::string line;
    while (getline(iFile, line)) {
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        if (line.size() < 8) continue;
        if (line.substr(0, 8) != "#include") continue;

        bool std;
        switch (line[8]) {
            case '"':
                std = false;
                break;
            case '<':
                std = true;
                break;
            default:
                continue;
        }

        int end = line.find_first_of(std ? '>' : '"', 9);
        if (end == std::string::npos) continue;

        std::string included = line.substr(9, end - 9);
        if (std) {
            file.includes.emplace(included, std);
            continue;
        }

        auto home = current_path();
        current_path(path.parent_path());
        auto rel = relative(absolute(included), home);
        current_path(home);

        file.includes.emplace(rel, std);
    }

    iFile.close();
    files[relative(path)] = file;

    for (const auto &include: file.includes) {  //files above working directory
        if (files.find(include.first) == files.end()) scanFile(absolute(include.first));
    }
}

void Scanner::print() {
    std::string dotName = temp_directory_path() / "includes.dot";
    std::string pngName = temp_directory_path() / "includes.png";
    std::ofstream oFile(dotName);
    if (!oFile.good()) return;

    oFile << "digraph includes{\n"
             "\tbgcolor=\"#252525\";\n"
             "\toutputorder=edgesfirst;\n"
             "\tresolution=250;\n\n"
             "\tnode [ color=\"#252525\", fillcolor=\"#505050\", fontcolor=white, height=0.5, width=0.75, fontname=roboto, shape=box, style=filled ];\n"
             "\tedge [ color=\"#505050\", penwidt=2.5 ];\n\n";

    for (const auto &file: files) {
        std::string color;
        if (file.second.implementation) {
            color = "#3BB33B";
        } else {
            color = "#E33B3B";
        }
        oFile << "\t\"" << file.first << "\" [ fillcolor=\"" << color << "\" ];\n\n";

        for (const auto &include: file.second.includes) {
            if (include.second) color = "#505050";
            else if (files.find(include.first) != files.end()) {
                if (files[include.first].implementation) color = "#3BB33B";
                else color = "#E33B3B";
            } else color = "#FF9000";

            oFile << "\t\"" << file.first << "\" -> \"" << include.first << "\" [ dir=back, color=\"" << color
                  << "\" ] ;\n";
        }
        oFile << "\n";
    }

    oFile << "\n\t{ rank=same; ";
    for (const auto &file: files) {
        for (const auto &include: file.second.includes) {
            if (!include.second) continue;
            oFile << "\"" << include.first << "\" ";
        }
    }
    oFile << "};\n";

    oFile << "}";

    oFile.close();
    std::string command =
            "(dot -Tpng " + dotName + " -o " + pngName + " && xdg-open " + pngName + ") &";
    system(command.c_str());
}

Scanner::Scanner(bool header) {
    (*this).header = header;
    scanFolder(current_path());
    print();
}

