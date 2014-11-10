# Compiler and flags definitions
# CXX is intended for local compiling; thus, all possible flags are set.
# WIN32CXX and WIN64CXX are meant for cross-compiling only, so we should
# not bother with warnings.
#
# One flag (RWINDOWS) is defined when cross-compiling for Windows; the main
# purpose is to execute getchar() in main() to prevent the console window to
# quit before viewing all output in Windows.
# The name RWINDOWS was chosen to avoid name clashes, because the name WINDOWS
# seems to be used by some system headers.
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -Werror -g
WIN32CXX := i686-w64-mingw32-g++
WIN64CXX := x86_64-w64-mingw32-g++
WINCXXFLAGS := -std=c++11 -w -static -lgcc -lstdc++ -lpthread -DRWINDOWS

# Variable definitions
SOURCES := $(shell find -name "*.cpp")
DEPS	:= $(SOURCES:.cpp=.d)
OBJ		:= $(SOURCES:.cpp=.o)

# Avaliable targets:

#	modelsim
# Default target.
# Builds with debug enabled and all possibly useful warnings.
#
# This makefile do the build by parts, separating each .cpp in a .o
# (the binary) and a .d (dependancy file; see below). This permits
# recompilation of only the changed object files during debugging.
modelsim: $(OBJ)
	$(CXX) $(OBJ) -o modelsim

#	all
# Builds both the host-system executable and the Windows executables.
all: modelsim win32 win64

# 	win32
# Cross-compiles the 32-bit binary for Windows.
#
# Since most of the debugging is done in the host system, there is no
# need to do complex dependency management for Windows targets;
win32: modelsim-win32.exe
modelsim-win32.exe: $(SOURCES)
	$(WIN32CXX) $(WINCXXFLAGS) -o modelsim-win32.exe $(SOURCES)

#	win64
# Cross-compiles the 64-bit binary for Windows.
win64: modelsim-win64.exe
modelsim-win64.exe: $(SOURCES)
	$(WIN64CXX) $(WINCXXFLAGS) -o modelsim-win64.exe $(SOURCES)

# Object files
# This script also rewrites the corresponding .d file, so that whenever an object file
# needs recompilation, the dependency file is updated.
$(OBJ): %.o : %.cpp
	$(CXX) $(CXXFLAGS) $(ILIBS) $(FINCLUDE) -c $< -o $@
	g++ -std=c++0x -MM $< -MF $*.d -MT "$*.o" $(ILIBS)
	sed -e 's/^.*://' -e 's/\\//' -e 's/ /\n/g' $*.d | sed -e 's/\(..*\)/\1:/' >> $*.d

-include $(DEPS)



.PHONY: win32 win64 clean veryclean test
clean:
	-find \( -name "*.o" -or -name "*.d" \) -exec rm '{}' \;

veryclean: clean
	-rm modelsim modelsim-win32.exe modelsim-win64.exe
