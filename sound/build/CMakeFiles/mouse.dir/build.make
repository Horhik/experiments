# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /nix/store/0s8gvg6nh3d3cbby1hjf69jfb2xdvbvp-cmake-3.25.3/bin/cmake

# The command to remove a file.
RM = /nix/store/0s8gvg6nh3d3cbby1hjf69jfb2xdvbvp-cmake-3.25.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/horhik/Code/Tinkering/sound

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/horhik/Code/Tinkering/sound/build

# Include any dependencies generated for this target.
include CMakeFiles/mouse.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mouse.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mouse.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mouse.dir/flags.make

CMakeFiles/mouse.dir/src/mouse.c.o: CMakeFiles/mouse.dir/flags.make
CMakeFiles/mouse.dir/src/mouse.c.o: /home/horhik/Code/Tinkering/sound/src/mouse.c
CMakeFiles/mouse.dir/src/mouse.c.o: CMakeFiles/mouse.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/horhik/Code/Tinkering/sound/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mouse.dir/src/mouse.c.o"
	/nix/store/90h6k8ylkgn81k10190v5c9ldyjpzgl9-gcc-wrapper-12.3.0/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/mouse.dir/src/mouse.c.o -MF CMakeFiles/mouse.dir/src/mouse.c.o.d -o CMakeFiles/mouse.dir/src/mouse.c.o -c /home/horhik/Code/Tinkering/sound/src/mouse.c

CMakeFiles/mouse.dir/src/mouse.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mouse.dir/src/mouse.c.i"
	/nix/store/90h6k8ylkgn81k10190v5c9ldyjpzgl9-gcc-wrapper-12.3.0/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/horhik/Code/Tinkering/sound/src/mouse.c > CMakeFiles/mouse.dir/src/mouse.c.i

CMakeFiles/mouse.dir/src/mouse.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mouse.dir/src/mouse.c.s"
	/nix/store/90h6k8ylkgn81k10190v5c9ldyjpzgl9-gcc-wrapper-12.3.0/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/horhik/Code/Tinkering/sound/src/mouse.c -o CMakeFiles/mouse.dir/src/mouse.c.s

# Object files for target mouse
mouse_OBJECTS = \
"CMakeFiles/mouse.dir/src/mouse.c.o"

# External object files for target mouse
mouse_EXTERNAL_OBJECTS =

mouse: CMakeFiles/mouse.dir/src/mouse.c.o
mouse: CMakeFiles/mouse.dir/build.make
mouse: /nix/store/ssy23r370b8q1nfmpa4nm8xx8yli22af-raylib-4.5.0/lib/libraylib.so
mouse: CMakeFiles/mouse.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/horhik/Code/Tinkering/sound/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable mouse"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mouse.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mouse.dir/build: mouse
.PHONY : CMakeFiles/mouse.dir/build

CMakeFiles/mouse.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mouse.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mouse.dir/clean

CMakeFiles/mouse.dir/depend:
	cd /home/horhik/Code/Tinkering/sound/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/horhik/Code/Tinkering/sound /home/horhik/Code/Tinkering/sound /home/horhik/Code/Tinkering/sound/build /home/horhik/Code/Tinkering/sound/build /home/horhik/Code/Tinkering/sound/build/CMakeFiles/mouse.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mouse.dir/depend
