# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.3.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.3.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/POiC__ZadanieZaliczeniowe.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/POiC__ZadanieZaliczeniowe.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/POiC__ZadanieZaliczeniowe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/POiC__ZadanieZaliczeniowe.dir/flags.make

CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.obj: CMakeFiles/POiC__ZadanieZaliczeniowe.dir/flags.make
CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.obj: C:/Users/jedrz/CLionProjects/POiC-ZadanieZaliczeniowe/main.cpp
CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.obj: CMakeFiles/POiC__ZadanieZaliczeniowe.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.obj -MF CMakeFiles\POiC__ZadanieZaliczeniowe.dir\main.cpp.obj.d -o CMakeFiles\POiC__ZadanieZaliczeniowe.dir\main.cpp.obj -c C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\main.cpp

CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\main.cpp > CMakeFiles\POiC__ZadanieZaliczeniowe.dir\main.cpp.i

CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\main.cpp -o CMakeFiles\POiC__ZadanieZaliczeniowe.dir\main.cpp.s

# Object files for target POiC__ZadanieZaliczeniowe
POiC__ZadanieZaliczeniowe_OBJECTS = \
"CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.obj"

# External object files for target POiC__ZadanieZaliczeniowe
POiC__ZadanieZaliczeniowe_EXTERNAL_OBJECTS =

POiC__ZadanieZaliczeniowe.exe: CMakeFiles/POiC__ZadanieZaliczeniowe.dir/main.cpp.obj
POiC__ZadanieZaliczeniowe.exe: CMakeFiles/POiC__ZadanieZaliczeniowe.dir/build.make
POiC__ZadanieZaliczeniowe.exe: CMakeFiles/POiC__ZadanieZaliczeniowe.dir/linklibs.rsp
POiC__ZadanieZaliczeniowe.exe: CMakeFiles/POiC__ZadanieZaliczeniowe.dir/objects1.rsp
POiC__ZadanieZaliczeniowe.exe: CMakeFiles/POiC__ZadanieZaliczeniowe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable POiC__ZadanieZaliczeniowe.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\POiC__ZadanieZaliczeniowe.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/POiC__ZadanieZaliczeniowe.dir/build: POiC__ZadanieZaliczeniowe.exe
.PHONY : CMakeFiles/POiC__ZadanieZaliczeniowe.dir/build

CMakeFiles/POiC__ZadanieZaliczeniowe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\POiC__ZadanieZaliczeniowe.dir\cmake_clean.cmake
.PHONY : CMakeFiles/POiC__ZadanieZaliczeniowe.dir/clean

CMakeFiles/POiC__ZadanieZaliczeniowe.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\cmake-build-debug C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\cmake-build-debug C:\Users\jedrz\CLionProjects\POiC-ZadanieZaliczeniowe\cmake-build-debug\CMakeFiles\POiC__ZadanieZaliczeniowe.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/POiC__ZadanieZaliczeniowe.dir/depend

