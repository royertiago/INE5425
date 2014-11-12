INE5425 - Modelagem e Simulação
=========================================================

Development of a simulator in a general-purpose language,
to the INE5425 (Modeling and Simulation) discipline.



Running
=======

TODO



Building
========

To build the program, you need a C++11-compliant compiler. The makefile
is set up to use g++ with -std=c++11. The makefile is also set up to use
i686-w64-mingw32-g++ and x86\_64-w64-mingw32-g++ to cross-compile 32- and
64-bit binaries for Windows; the easiest way to get these programs is to

    sudo apt-get install mingw-w64

Makefile targets
----------------

    make modelsim

Builds the binary `modelsim` for the host system. This is the default.
Since this is intended for development, this target also builds each
.cpp into a .o separately. With an additional .d per .cpp, the makefile
system is able to recompile only the affected modules by source code
modifications. 

    make win32

Builds the binary `modelsim-win32.exe` for Windows.

    make win64

Builds the binary `modelsim-win64.exe` for Windows.

    make all

Builds all the above.
