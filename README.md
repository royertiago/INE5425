INE5425 - Modelagem e Simulação
=========================================================

Development of a simulator in a general-purpose language,
to the INE5425 (Modeling and Simulation) discipline.



Building
========

To build the program, you need a C++11-compliant compiler. The makefile
is set up to use g++ with -std=c++11. The makefile is also set up to use
i686-w64-mingw32-g++ and x86\_64-w64-mingw32-g++ to cross-compile 32- and
64-bit binaries for Windows; the easiest way to get these programs is to

    sudo apt-get install mingw-w64

To build and run the tests, you need the Catch unit test framework.
You can get the submodules by using `git clone --recursive` when cloning
or running `git submodule init` and `git submodule add` on the Catch
empty directory.


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

    make test

Builds and runs all unit tests. This is the only target that actually
needs the Catch framework; the above three will work just fine with
only g++-4.8 and (for Windows cross-build) mingw-W64.

    make all

Builds all the above.
