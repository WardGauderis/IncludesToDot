# IncludesToDot

By Ward Gauderis

Visualize and optimize the include structure of your C/C++ project on Linux using Graphviz DOT language.

Dependencies: the Graphviz package

Usage: itd <path (optional)> -<options (optional)>
- if path is a file, only included files will be scanned recursively (without 'r')
- if path is a folder all files in the underlying folders will be scanned together with their includes recursively (without 'r')
- r - do not scan files recursively
- h - hide headers and their library/missing dependencies
- c - hide implementation files and their library/missing dependencies
- l - hide library dependencies
- u - hide unknown/missing dependencies
- o - show the optimized graph of your project's includes (using transitive reduction)
- O - same as 'o' but applies these changes to your files (backups are made in the backup folder)

Examples:   
- itd main.cpp -olu
- itd myProject/src/ -lc
            
Graph color:
- red - header file/include
- green - implementation file/include
- grey - library file/include
- orange - unknown/missing file/include
