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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build

# Include any dependencies generated for this target.
include example/CMakeFiles/scp_write_nonblock.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include example/CMakeFiles/scp_write_nonblock.dir/compiler_depend.make

# Include the progress variables for this target.
include example/CMakeFiles/scp_write_nonblock.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/scp_write_nonblock.dir/flags.make

example/CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o: example/CMakeFiles/scp_write_nonblock.dir/flags.make
example/CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o: ../example/scp_write_nonblock.c
example/CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o: example/CMakeFiles/scp_write_nonblock.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object example/CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/example && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT example/CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o -MF CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o.d -o CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o -c /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/example/scp_write_nonblock.c

example/CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.i"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/example && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/example/scp_write_nonblock.c > CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.i

example/CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.s"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/example && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/example/scp_write_nonblock.c -o CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.s

# Object files for target scp_write_nonblock
scp_write_nonblock_OBJECTS = \
"CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o"

# External object files for target scp_write_nonblock
scp_write_nonblock_EXTERNAL_OBJECTS =

example/scp_write_nonblock: example/CMakeFiles/scp_write_nonblock.dir/scp_write_nonblock.c.o
example/scp_write_nonblock: example/CMakeFiles/scp_write_nonblock.dir/build.make
example/scp_write_nonblock: src/libssh2.so.1.0.1
example/scp_write_nonblock: /usr/lib64/libssl.so
example/scp_write_nonblock: /usr/lib64/libcrypto.so
example/scp_write_nonblock: /usr/lib64/libz.so
example/scp_write_nonblock: example/CMakeFiles/scp_write_nonblock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable scp_write_nonblock"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/scp_write_nonblock.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/scp_write_nonblock.dir/build: example/scp_write_nonblock
.PHONY : example/CMakeFiles/scp_write_nonblock.dir/build

example/CMakeFiles/scp_write_nonblock.dir/clean:
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/example && $(CMAKE_COMMAND) -P CMakeFiles/scp_write_nonblock.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/scp_write_nonblock.dir/clean

example/CMakeFiles/scp_write_nonblock.dir/depend:
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0 /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/example /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/example /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/example/CMakeFiles/scp_write_nonblock.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/scp_write_nonblock.dir/depend

