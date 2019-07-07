//============================================================================
// @name        : main.cpp
// @author      : Ward Gauderis
// @date        : 7/7/19
// @version     :
// @copyright   : BA1 Informatica - Ward Gauderis - University of Antwerp
// @description :
//============================================================================
#include "Scanner.h"
#include <vector>
#include <iostream>

int main(int argc, char *argv[]) {
    std::vector<std::string> arguments(argv + 1, argv + argc);

    bool headers = argc > 1 && arguments[0] == "-h";

    std::cout << "IncludesToDot\n"
                 "By Ward Gauderis\n"
                 "Visualize the include structure of your C++ project on Linux using Graphviz DOT language.\n\n"
                 "Dependencies: the Graphviz package\n"
                 "Usage: -h for headers only\n\n"
                 "Node color:   grey - library/missing file\n"
                 "              green - implementation file\n"
                 "              red - header file\n"
                 "Edge color:   grey - include libraries\n"
                 "              green - include implementation file (?)\n"
                 "              red - include header file\n"
                 "              orange - include missing file\n";

    Scanner scanner(headers);

    return 0;
}

