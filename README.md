# IncludesToDot

By Ward Gauderis

Visualize the include structure of your C++ project on Linux using Graphviz DOT language.

Dependencies: the Graphviz package

Usage:        
- h - hide headers
- c - hide implementation files
- l - hide libraries

Node color:   
- grey - library/missing file
- green - implementation file
- red - header file
              
Edge color:
- grey - include libraries
- green - include implementation file (?)
- red - include header file
- orange - include missing file
