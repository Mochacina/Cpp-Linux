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
include tests/CMakeFiles/test_auth_keyboard_ok.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/test_auth_keyboard_ok.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_auth_keyboard_ok.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_auth_keyboard_ok.dir/flags.make

tests/CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o: tests/CMakeFiles/test_auth_keyboard_ok.dir/flags.make
tests/CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o: ../tests/test_auth_keyboard_ok.c
tests/CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o: tests/CMakeFiles/test_auth_keyboard_ok.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT tests/CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o -MF CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o.d -o CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o -c /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/tests/test_auth_keyboard_ok.c

tests/CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.i"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/tests/test_auth_keyboard_ok.c > CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.i

tests/CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.s"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/tests/test_auth_keyboard_ok.c -o CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.s

# Object files for target test_auth_keyboard_ok
test_auth_keyboard_ok_OBJECTS = \
"CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o"

# External object files for target test_auth_keyboard_ok
test_auth_keyboard_ok_EXTERNAL_OBJECTS =

tests/test_auth_keyboard_ok: tests/CMakeFiles/test_auth_keyboard_ok.dir/test_auth_keyboard_ok.c.o
tests/test_auth_keyboard_ok: tests/CMakeFiles/test_auth_keyboard_ok.dir/build.make
tests/test_auth_keyboard_ok: tests/librunner.a
tests/test_auth_keyboard_ok: src/libssh2.so.1.0.1
tests/test_auth_keyboard_ok: /usr/lib64/libssl.so
tests/test_auth_keyboard_ok: /usr/lib64/libcrypto.so
tests/test_auth_keyboard_ok: /usr/lib64/libz.so
tests/test_auth_keyboard_ok: tests/CMakeFiles/test_auth_keyboard_ok.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_auth_keyboard_ok"
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_auth_keyboard_ok.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_auth_keyboard_ok.dir/build: tests/test_auth_keyboard_ok
.PHONY : tests/CMakeFiles/test_auth_keyboard_ok.dir/build

tests/CMakeFiles/test_auth_keyboard_ok.dir/clean:
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_auth_keyboard_ok.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_auth_keyboard_ok.dir/clean

tests/CMakeFiles/test_auth_keyboard_ok.dir/depend:
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0 /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/tests /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests/CMakeFiles/test_auth_keyboard_ok.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_auth_keyboard_ok.dir/depend

