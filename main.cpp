//============================================================================
// @name        : main.cpp
// @author      : Ward Gauderis
// @date        : 7/7/19
// @version     :
// @copyright   : BA1 Informatica - Ward Gauderis - University of Antwerp
// @description :
//============================================================================
#include "Scanner.h"
#include <iostream>
#include <algorithm>
#include <vector>

int main(int argc, char *argv[]) {
    std::vector<std::string> arguments(argv + 1, argv + argc);

    char c = 'h';
    auto find = [&c](const std::string &arg) { return arg.find(c) != std::string::npos; };

    bool header = std::find_if(arguments.begin(), arguments.end(), find) != arguments.end();

    c = 'c';
    bool implementation = std::find_if(arguments.begin(), arguments.end(), find) != arguments.end();

    c = 'l';
    bool library = std::find_if(arguments.begin(), arguments.end(), find) != arguments.end();

    std::cout << "IncludesToDot\n"
                 "By Ward Gauderis\n"
                 "Visualize the include structure of your C++ project on Linux using Graphviz DOT language.\n\n"
                 "Dependencies: the Graphviz package\n"
                 "Usage:        h - hide headers\n"
                 "              c - hide implementation files\n"
                 "              l - hide libraries\n\n"
                 "Node color:   grey - library/missing file\n"
                 "              green - implementation file\n"
                 "              red - header file\n"
                 "Edge color:   grey - include libraries\n"
                 "              green - include implementation file (?)\n"
                 "              red - include header file\n"
                 "              orange - include missing file\n";

    Scanner scanner(header, implementation, library);

    return 0;
}

