# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ejemplo3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ejemplo3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ejemplo3.dir/flags.make

CMakeFiles/ejemplo3.dir/main3.cc.o: CMakeFiles/ejemplo3.dir/flags.make
CMakeFiles/ejemplo3.dir/main3.cc.o: ../main3.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ejemplo3.dir/main3.cc.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ejemplo3.dir/main3.cc.o -c /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/main3.cc

CMakeFiles/ejemplo3.dir/main3.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ejemplo3.dir/main3.cc.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/main3.cc > CMakeFiles/ejemplo3.dir/main3.cc.i

CMakeFiles/ejemplo3.dir/main3.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ejemplo3.dir/main3.cc.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/main3.cc -o CMakeFiles/ejemplo3.dir/main3.cc.s

CMakeFiles/ejemplo3.dir/Semaforo.cpp.o: CMakeFiles/ejemplo3.dir/flags.make
CMakeFiles/ejemplo3.dir/Semaforo.cpp.o: ../Semaforo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ejemplo3.dir/Semaforo.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ejemplo3.dir/Semaforo.cpp.o -c /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/Semaforo.cpp

CMakeFiles/ejemplo3.dir/Semaforo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ejemplo3.dir/Semaforo.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/Semaforo.cpp > CMakeFiles/ejemplo3.dir/Semaforo.cpp.i

CMakeFiles/ejemplo3.dir/Semaforo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ejemplo3.dir/Semaforo.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/Semaforo.cpp -o CMakeFiles/ejemplo3.dir/Semaforo.cpp.s

# Object files for target ejemplo3
ejemplo3_OBJECTS = \
"CMakeFiles/ejemplo3.dir/main3.cc.o" \
"CMakeFiles/ejemplo3.dir/Semaforo.cpp.o"

# External object files for target ejemplo3
ejemplo3_EXTERNAL_OBJECTS =

ejemplo3: CMakeFiles/ejemplo3.dir/main3.cc.o
ejemplo3: CMakeFiles/ejemplo3.dir/Semaforo.cpp.o
ejemplo3: CMakeFiles/ejemplo3.dir/build.make
ejemplo3: CMakeFiles/ejemplo3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ejemplo3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ejemplo3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ejemplo3.dir/build: ejemplo3

.PHONY : CMakeFiles/ejemplo3.dir/build

CMakeFiles/ejemplo3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ejemplo3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ejemplo3.dir/clean

CMakeFiles/ejemplo3.dir/depend:
	cd /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/cmake-build-debug /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/cmake-build-debug /Users/Jazmina/Documents/FIUBA/concurrentes/practica/ejercicios/pizza/cmake-build-debug/CMakeFiles/ejemplo3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ejemplo3.dir/depend
