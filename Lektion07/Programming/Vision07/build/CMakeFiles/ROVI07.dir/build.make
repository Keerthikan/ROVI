# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/student/ROVI/Lektion07/Programming/Vision07/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student/ROVI/Lektion07/Programming/Vision07/build

# Include any dependencies generated for this target.
include CMakeFiles/ROVI07.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ROVI07.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ROVI07.dir/flags.make

CMakeFiles/ROVI07.dir/ROVI07.cpp.o: CMakeFiles/ROVI07.dir/flags.make
CMakeFiles/ROVI07.dir/ROVI07.cpp.o: /home/student/ROVI/Lektion07/Programming/Vision07/src/ROVI07.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/student/ROVI/Lektion07/Programming/Vision07/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ROVI07.dir/ROVI07.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ROVI07.dir/ROVI07.cpp.o -c /home/student/ROVI/Lektion07/Programming/Vision07/src/ROVI07.cpp

CMakeFiles/ROVI07.dir/ROVI07.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ROVI07.dir/ROVI07.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/student/ROVI/Lektion07/Programming/Vision07/src/ROVI07.cpp > CMakeFiles/ROVI07.dir/ROVI07.cpp.i

CMakeFiles/ROVI07.dir/ROVI07.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ROVI07.dir/ROVI07.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/student/ROVI/Lektion07/Programming/Vision07/src/ROVI07.cpp -o CMakeFiles/ROVI07.dir/ROVI07.cpp.s

CMakeFiles/ROVI07.dir/ROVI07.cpp.o.requires:
.PHONY : CMakeFiles/ROVI07.dir/ROVI07.cpp.o.requires

CMakeFiles/ROVI07.dir/ROVI07.cpp.o.provides: CMakeFiles/ROVI07.dir/ROVI07.cpp.o.requires
	$(MAKE) -f CMakeFiles/ROVI07.dir/build.make CMakeFiles/ROVI07.dir/ROVI07.cpp.o.provides.build
.PHONY : CMakeFiles/ROVI07.dir/ROVI07.cpp.o.provides

CMakeFiles/ROVI07.dir/ROVI07.cpp.o.provides.build: CMakeFiles/ROVI07.dir/ROVI07.cpp.o

# Object files for target ROVI07
ROVI07_OBJECTS = \
"CMakeFiles/ROVI07.dir/ROVI07.cpp.o"

# External object files for target ROVI07
ROVI07_EXTERNAL_OBJECTS =

ROVI07: CMakeFiles/ROVI07.dir/ROVI07.cpp.o
ROVI07: CMakeFiles/ROVI07.dir/build.make
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_ts.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_nonfree.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_nonfree.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_ocl.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4.8
ROVI07: /usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4.8
ROVI07: CMakeFiles/ROVI07.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ROVI07"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ROVI07.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ROVI07.dir/build: ROVI07
.PHONY : CMakeFiles/ROVI07.dir/build

CMakeFiles/ROVI07.dir/requires: CMakeFiles/ROVI07.dir/ROVI07.cpp.o.requires
.PHONY : CMakeFiles/ROVI07.dir/requires

CMakeFiles/ROVI07.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ROVI07.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ROVI07.dir/clean

CMakeFiles/ROVI07.dir/depend:
	cd /home/student/ROVI/Lektion07/Programming/Vision07/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/student/ROVI/Lektion07/Programming/Vision07/src /home/student/ROVI/Lektion07/Programming/Vision07/src /home/student/ROVI/Lektion07/Programming/Vision07/build /home/student/ROVI/Lektion07/Programming/Vision07/build /home/student/ROVI/Lektion07/Programming/Vision07/build/CMakeFiles/ROVI07.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ROVI07.dir/depend

