# IncludesToDot

Visualize the include structure of your C++ project on Linux using Graphviz DOT language.

Dependencies: the Graphviz package

Usage: -h for headers only

Node color:   
- grey - library/missing file
- green - implementation file
- red - header file
              
Edge color:
- grey - include libraries
- green - include implementation file (?)
- red - include header file
- orange - include missing file
