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
CMAKE_SOURCE_DIR = /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build

# Include any dependencies generated for this target.
include example/CMakeFiles/example-subsystem_netconf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include example/CMakeFiles/example-subsystem_netconf.dir/compiler_depend.make

# Include the progress variables for this target.
include example/CMakeFiles/example-subsystem_netconf.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/example-subsystem_netconf.dir/flags.make

example/CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o: example/CMakeFiles/example-subsystem_netconf.dir/flags.make
example/CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o: ../example/subsystem_netconf.c
example/CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o: example/CMakeFiles/example-subsystem_netconf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object example/CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/example && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT example/CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o -MF CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o.d -o CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o -c /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/example/subsystem_netconf.c

example/CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.i"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/example && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/example/subsystem_netconf.c > CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.i

example/CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.s"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/example && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/example/subsystem_netconf.c -o CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.s

# Object files for target example-subsystem_netconf
example__subsystem_netconf_OBJECTS = \
"CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o"

# External object files for target example-subsystem_netconf
example__subsystem_netconf_EXTERNAL_OBJECTS =

example/example-subsystem_netconf: example/CMakeFiles/example-subsystem_netconf.dir/subsystem_netconf.c.o
example/example-subsystem_netconf: example/CMakeFiles/example-subsystem_netconf.dir/build.make
example/example-subsystem_netconf: src/libssh2.a
example/example-subsystem_netconf: /usr/lib64/libssl.so
example/example-subsystem_netconf: /usr/lib64/libcrypto.so
example/example-subsystem_netconf: example/CMakeFiles/example-subsystem_netconf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable example-subsystem_netconf"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example-subsystem_netconf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/example-subsystem_netconf.dir/build: example/example-subsystem_netconf
.PHONY : example/CMakeFiles/example-subsystem_netconf.dir/build

example/CMakeFiles/example-subsystem_netconf.dir/clean:
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/example && $(CMAKE_COMMAND) -P CMakeFiles/example-subsystem_netconf.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/example-subsystem_netconf.dir/clean

example/CMakeFiles/example-subsystem_netconf.dir/depend:
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0 /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/example /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/example /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.8.0/build/example/CMakeFiles/example-subsystem_netconf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/example-subsystem_netconf.dir/depend

