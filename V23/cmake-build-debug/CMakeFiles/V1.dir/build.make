# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /home/ludovic/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5457.51/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ludovic/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/212.5457.51/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ludovic/Bureau/L2/PA/PROJET/V17

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/V1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/V1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/V1.dir/flags.make

CMakeFiles/V1.dir/data.c.o: CMakeFiles/V1.dir/flags.make
CMakeFiles/V1.dir/data.c.o: ../data.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/V1.dir/data.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/V1.dir/data.c.o -c /home/ludovic/Bureau/L2/PA/PROJET/V17/data.c

CMakeFiles/V1.dir/data.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/V1.dir/data.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ludovic/Bureau/L2/PA/PROJET/V17/data.c > CMakeFiles/V1.dir/data.c.i

CMakeFiles/V1.dir/data.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/V1.dir/data.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ludovic/Bureau/L2/PA/PROJET/V17/data.c -o CMakeFiles/V1.dir/data.c.s

CMakeFiles/V1.dir/fonctions_SDL.c.o: CMakeFiles/V1.dir/flags.make
CMakeFiles/V1.dir/fonctions_SDL.c.o: ../fonctions_SDL.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/V1.dir/fonctions_SDL.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/V1.dir/fonctions_SDL.c.o -c /home/ludovic/Bureau/L2/PA/PROJET/V17/fonctions_SDL.c

CMakeFiles/V1.dir/fonctions_SDL.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/V1.dir/fonctions_SDL.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ludovic/Bureau/L2/PA/PROJET/V17/fonctions_SDL.c > CMakeFiles/V1.dir/fonctions_SDL.c.i

CMakeFiles/V1.dir/fonctions_SDL.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/V1.dir/fonctions_SDL.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ludovic/Bureau/L2/PA/PROJET/V17/fonctions_SDL.c -o CMakeFiles/V1.dir/fonctions_SDL.c.s

CMakeFiles/V1.dir/main.c.o: CMakeFiles/V1.dir/flags.make
CMakeFiles/V1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/V1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/V1.dir/main.c.o -c /home/ludovic/Bureau/L2/PA/PROJET/V17/main.c

CMakeFiles/V1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/V1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ludovic/Bureau/L2/PA/PROJET/V17/main.c > CMakeFiles/V1.dir/main.c.i

CMakeFiles/V1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/V1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ludovic/Bureau/L2/PA/PROJET/V17/main.c -o CMakeFiles/V1.dir/main.c.s

# Object files for target V1
V1_OBJECTS = \
"CMakeFiles/V1.dir/data.c.o" \
"CMakeFiles/V1.dir/fonctions_SDL.c.o" \
"CMakeFiles/V1.dir/main.c.o"

# External object files for target V1
V1_EXTERNAL_OBJECTS =

V1: CMakeFiles/V1.dir/data.c.o
V1: CMakeFiles/V1.dir/fonctions_SDL.c.o
V1: CMakeFiles/V1.dir/main.c.o
V1: CMakeFiles/V1.dir/build.make
V1: CMakeFiles/V1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable V1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/V1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/V1.dir/build: V1
.PHONY : CMakeFiles/V1.dir/build

CMakeFiles/V1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/V1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/V1.dir/clean

CMakeFiles/V1.dir/depend:
	cd /home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ludovic/Bureau/L2/PA/PROJET/V17 /home/ludovic/Bureau/L2/PA/PROJET/V17 /home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug /home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug /home/ludovic/Bureau/L2/PA/PROJET/V17/cmake-build-debug/CMakeFiles/V1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/V1.dir/depend

