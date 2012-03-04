# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /opt/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/iaefai/Code/Ray

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/iaefai/Code/Ray

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/opt/local/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/opt/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/iaefai/Code/Ray/CMakeFiles /Users/iaefai/Code/Ray/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/iaefai/Code/Ray/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ray

# Build rule for target.
ray: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ray
.PHONY : ray

# fast build rule for target.
ray/fast:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/build
.PHONY : ray/fast

src/geometry.o: src/geometry.cpp.o
.PHONY : src/geometry.o

# target to build an object file
src/geometry.cpp.o:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/geometry.cpp.o
.PHONY : src/geometry.cpp.o

src/geometry.i: src/geometry.cpp.i
.PHONY : src/geometry.i

# target to preprocess a source file
src/geometry.cpp.i:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/geometry.cpp.i
.PHONY : src/geometry.cpp.i

src/geometry.s: src/geometry.cpp.s
.PHONY : src/geometry.s

# target to generate assembly for a file
src/geometry.cpp.s:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/geometry.cpp.s
.PHONY : src/geometry.cpp.s

src/lodepng.o: src/lodepng.cpp.o
.PHONY : src/lodepng.o

# target to build an object file
src/lodepng.cpp.o:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/lodepng.cpp.o
.PHONY : src/lodepng.cpp.o

src/lodepng.i: src/lodepng.cpp.i
.PHONY : src/lodepng.i

# target to preprocess a source file
src/lodepng.cpp.i:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/lodepng.cpp.i
.PHONY : src/lodepng.cpp.i

src/lodepng.s: src/lodepng.cpp.s
.PHONY : src/lodepng.s

# target to generate assembly for a file
src/lodepng.cpp.s:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/lodepng.cpp.s
.PHONY : src/lodepng.cpp.s

src/ray.o: src/ray.cpp.o
.PHONY : src/ray.o

# target to build an object file
src/ray.cpp.o:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/ray.cpp.o
.PHONY : src/ray.cpp.o

src/ray.i: src/ray.cpp.i
.PHONY : src/ray.i

# target to preprocess a source file
src/ray.cpp.i:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/ray.cpp.i
.PHONY : src/ray.cpp.i

src/ray.s: src/ray.cpp.s
.PHONY : src/ray.s

# target to generate assembly for a file
src/ray.cpp.s:
	$(MAKE) -f CMakeFiles/ray.dir/build.make CMakeFiles/ray.dir/src/ray.cpp.s
.PHONY : src/ray.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... ray"
	@echo "... rebuild_cache"
	@echo "... src/geometry.o"
	@echo "... src/geometry.i"
	@echo "... src/geometry.s"
	@echo "... src/lodepng.o"
	@echo "... src/lodepng.i"
	@echo "... src/lodepng.s"
	@echo "... src/ray.o"
	@echo "... src/ray.i"
	@echo "... src/ray.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
