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

# Utility rule file for copy_test_dependencies.

# Include any custom commands dependencies for this target.
include tests/CMakeFiles/copy_test_dependencies.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/copy_test_dependencies.dir/progress.make

copy_test_dependencies: tests/CMakeFiles/copy_test_dependencies.dir/build.make
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests && /usr/bin/cmake -E make_directory /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests/.
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests && /usr/bin/cmake -E copy /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/src/libssh2.so.1.0.1 /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests/.
.PHONY : copy_test_dependencies

# Rule to build all files generated by this target.
tests/CMakeFiles/copy_test_dependencies.dir/build: copy_test_dependencies
.PHONY : tests/CMakeFiles/copy_test_dependencies.dir/build

tests/CMakeFiles/copy_test_dependencies.dir/clean:
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/copy_test_dependencies.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/copy_test_dependencies.dir/clean

tests/CMakeFiles/copy_test_dependencies.dir/depend:
	cd /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0 /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/tests /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests /home/sohss/Cpp-Linux/libssh2Test/libssh2-1.11.0/build/tests/CMakeFiles/copy_test_dependencies.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/copy_test_dependencies.dir/depend
