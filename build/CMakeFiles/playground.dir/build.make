# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build"

# Include any dependencies generated for this target.
include CMakeFiles/playground.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/playground.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/playground.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/playground.dir/flags.make

CMakeFiles/playground.dir/src/playground.cc.o: CMakeFiles/playground.dir/flags.make
CMakeFiles/playground.dir/src/playground.cc.o: ../src/playground.cc
CMakeFiles/playground.dir/src/playground.cc.o: CMakeFiles/playground.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/playground.dir/src/playground.cc.o"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/playground.dir/src/playground.cc.o -MF CMakeFiles/playground.dir/src/playground.cc.o.d -o CMakeFiles/playground.dir/src/playground.cc.o -c "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/playground.cc"

CMakeFiles/playground.dir/src/playground.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/playground.dir/src/playground.cc.i"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/playground.cc" > CMakeFiles/playground.dir/src/playground.cc.i

CMakeFiles/playground.dir/src/playground.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/playground.dir/src/playground.cc.s"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/playground.cc" -o CMakeFiles/playground.dir/src/playground.cc.s

# Object files for target playground
playground_OBJECTS = \
"CMakeFiles/playground.dir/src/playground.cc.o"

# External object files for target playground
playground_EXTERNAL_OBJECTS =

playground: CMakeFiles/playground.dir/src/playground.cc.o
playground: CMakeFiles/playground.dir/build.make
playground: CMakeFiles/playground.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable playground"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/playground.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/playground.dir/build: playground
.PHONY : CMakeFiles/playground.dir/build

CMakeFiles/playground.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/playground.dir/cmake_clean.cmake
.PHONY : CMakeFiles/playground.dir/clean

CMakeFiles/playground.dir/depend:
	cd "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build/CMakeFiles/playground.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/playground.dir/depend
