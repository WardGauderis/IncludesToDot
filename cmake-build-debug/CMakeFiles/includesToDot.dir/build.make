# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ward/Documents/GitHub/IncludesToDot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ward/Documents/GitHub/IncludesToDot/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/includesToDot.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/includesToDot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/includesToDot.dir/flags.make

CMakeFiles/includesToDot.dir/Scanner.cpp.o: CMakeFiles/includesToDot.dir/flags.make
CMakeFiles/includesToDot.dir/Scanner.cpp.o: ../Scanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ward/Documents/GitHub/IncludesToDot/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/includesToDot.dir/Scanner.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/includesToDot.dir/Scanner.cpp.o -c /home/ward/Documents/GitHub/IncludesToDot/Scanner.cpp

CMakeFiles/includesToDot.dir/Scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/includesToDot.dir/Scanner.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ward/Documents/GitHub/IncludesToDot/Scanner.cpp > CMakeFiles/includesToDot.dir/Scanner.cpp.i

CMakeFiles/includesToDot.dir/Scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/includesToDot.dir/Scanner.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ward/Documents/GitHub/IncludesToDot/Scanner.cpp -o CMakeFiles/includesToDot.dir/Scanner.cpp.s

CMakeFiles/includesToDot.dir/main.cpp.o: CMakeFiles/includesToDot.dir/flags.make
CMakeFiles/includesToDot.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ward/Documents/GitHub/IncludesToDot/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/includesToDot.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/includesToDot.dir/main.cpp.o -c /home/ward/Documents/GitHub/IncludesToDot/main.cpp

CMakeFiles/includesToDot.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/includesToDot.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ward/Documents/GitHub/IncludesToDot/main.cpp > CMakeFiles/includesToDot.dir/main.cpp.i

CMakeFiles/includesToDot.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/includesToDot.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ward/Documents/GitHub/IncludesToDot/main.cpp -o CMakeFiles/includesToDot.dir/main.cpp.s

# Object files for target includesToDot
includesToDot_OBJECTS = \
"CMakeFiles/includesToDot.dir/Scanner.cpp.o" \
"CMakeFiles/includesToDot.dir/main.cpp.o"

# External object files for target includesToDot
includesToDot_EXTERNAL_OBJECTS =

includesToDot: CMakeFiles/includesToDot.dir/Scanner.cpp.o
includesToDot: CMakeFiles/includesToDot.dir/main.cpp.o
includesToDot: CMakeFiles/includesToDot.dir/build.make
includesToDot: CMakeFiles/includesToDot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ward/Documents/GitHub/IncludesToDot/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable includesToDot"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/includesToDot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/includesToDot.dir/build: includesToDot

.PHONY : CMakeFiles/includesToDot.dir/build

CMakeFiles/includesToDot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/includesToDot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/includesToDot.dir/clean

CMakeFiles/includesToDot.dir/depend:
	cd /home/ward/Documents/GitHub/IncludesToDot/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ward/Documents/GitHub/IncludesToDot /home/ward/Documents/GitHub/IncludesToDot /home/ward/Documents/GitHub/IncludesToDot/cmake-build-debug /home/ward/Documents/GitHub/IncludesToDot/cmake-build-debug /home/ward/Documents/GitHub/IncludesToDot/cmake-build-debug/CMakeFiles/includesToDot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/includesToDot.dir/depend
