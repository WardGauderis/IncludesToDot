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

int main(int argc, char *argv[]) {
    std::vector<std::string> arguments(argv + 1, argv + argc);

    bool u = true, h = true, c = true, l = true, r = true, o = false;
    path p = current_path();

    int path = 0, options = 0;

    for (const auto &arg: arguments) {
        if (arg[0] == '-') {
            u = arg.find('u') == std::string::npos;
            h = arg.find('h') == std::string::npos;
            c = arg.find('c') == std::string::npos;
            l = arg.find('l') == std::string::npos;
            r = arg.find('r') == std::string::npos;

            o = arg.find('o') != std::string::npos;
            ++options;
        } else {
            if (arg[0] == '/') {
                p = arg;
            } else {
                p = canonical(arg);
            }
            ++path;
        }
    }

    if (path > 1 || options > 1 || arguments.size() > 2 ||
        (arguments.size() > 0 && (arguments[0] == "--help"))) {
        std::cout << "IncludesToDot\n"
                     "By Ward Gauderis\n"
                     "Visualize the include structure of your C/C++ project on Linux using Graphviz DOT language.\n"
                     "Dependencies: the Graphviz package\n\n"
                     "Usage:        itd <path (optional)> -<options (optional)>\n"
                     "              h - hide headers and their library/missing dependencies\n"
                     "              c - hide implementation files and their library/missing dependencies\n"
                     "              l - hide library dependencies\n"
                     "              u - hide unknown/missing dependencies\n"
                     "              o - show the optimized graph of your project's includes (using transitive reduction)\n"
                     "Examples:     itd main.cpp -olu\n"
                     "              itd myProject/src/ -lc\n"
                     "Graph color:  red - header file/include\n"
                     "              green - implementation file/include\n"
                     "              grey - library file/include\n"
                     "              orange - unknown/missing file/include\n";
        return 1;
    }

    Scanner scanner(u, h, c, l, r, p);

    if (o) {
        scanner.transitiveReduction();
    }

    scanner.print();

    return 0;
}

