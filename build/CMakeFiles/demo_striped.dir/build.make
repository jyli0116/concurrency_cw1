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
include CMakeFiles/demo_striped.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/demo_striped.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/demo_striped.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/demo_striped.dir/flags.make

CMakeFiles/demo_striped.dir/src/benchmark.cc.o: CMakeFiles/demo_striped.dir/flags.make
CMakeFiles/demo_striped.dir/src/benchmark.cc.o: ../src/benchmark.cc
CMakeFiles/demo_striped.dir/src/benchmark.cc.o: CMakeFiles/demo_striped.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/demo_striped.dir/src/benchmark.cc.o"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo_striped.dir/src/benchmark.cc.o -MF CMakeFiles/demo_striped.dir/src/benchmark.cc.o.d -o CMakeFiles/demo_striped.dir/src/benchmark.cc.o -c "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/benchmark.cc"

CMakeFiles/demo_striped.dir/src/benchmark.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo_striped.dir/src/benchmark.cc.i"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/benchmark.cc" > CMakeFiles/demo_striped.dir/src/benchmark.cc.i

CMakeFiles/demo_striped.dir/src/benchmark.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo_striped.dir/src/benchmark.cc.s"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/benchmark.cc" -o CMakeFiles/demo_striped.dir/src/benchmark.cc.s

CMakeFiles/demo_striped.dir/src/demo_striped.cc.o: CMakeFiles/demo_striped.dir/flags.make
CMakeFiles/demo_striped.dir/src/demo_striped.cc.o: ../src/demo_striped.cc
CMakeFiles/demo_striped.dir/src/demo_striped.cc.o: CMakeFiles/demo_striped.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/demo_striped.dir/src/demo_striped.cc.o"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/demo_striped.dir/src/demo_striped.cc.o -MF CMakeFiles/demo_striped.dir/src/demo_striped.cc.o.d -o CMakeFiles/demo_striped.dir/src/demo_striped.cc.o -c "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/demo_striped.cc"

CMakeFiles/demo_striped.dir/src/demo_striped.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/demo_striped.dir/src/demo_striped.cc.i"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/demo_striped.cc" > CMakeFiles/demo_striped.dir/src/demo_striped.cc.i

CMakeFiles/demo_striped.dir/src/demo_striped.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/demo_striped.dir/src/demo_striped.cc.s"
	/usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/src/demo_striped.cc" -o CMakeFiles/demo_striped.dir/src/demo_striped.cc.s

# Object files for target demo_striped
demo_striped_OBJECTS = \
"CMakeFiles/demo_striped.dir/src/benchmark.cc.o" \
"CMakeFiles/demo_striped.dir/src/demo_striped.cc.o"

# External object files for target demo_striped
demo_striped_EXTERNAL_OBJECTS =

demo_striped: CMakeFiles/demo_striped.dir/src/benchmark.cc.o
demo_striped: CMakeFiles/demo_striped.dir/src/demo_striped.cc.o
demo_striped: CMakeFiles/demo_striped.dir/build.make
demo_striped: CMakeFiles/demo_striped.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable demo_striped"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/demo_striped.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/demo_striped.dir/build: demo_striped
.PHONY : CMakeFiles/demo_striped.dir/build

CMakeFiles/demo_striped.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/demo_striped.dir/cmake_clean.cmake
.PHONY : CMakeFiles/demo_striped.dir/clean

CMakeFiles/demo_striped.dir/depend:
	cd "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build" "/mnt/c/Users/jyli0/General/IMPERIAL/Y3_2425/60007 The Theory and Practise of Concurrency/skeleton/build/CMakeFiles/demo_striped.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/demo_striped.dir/depend
