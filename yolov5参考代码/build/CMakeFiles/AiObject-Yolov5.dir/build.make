# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/tc-eb5/local/1025/Aiobject-yolov5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tc-eb5/local/1025/Aiobject-yolov5/build

# Include any dependencies generated for this target.
include CMakeFiles/AiObject-Yolov5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AiObject-Yolov5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AiObject-Yolov5.dir/flags.make

CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o: CMakeFiles/AiObject-Yolov5.dir/flags.make
CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o: ../src/time_utility.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tc-eb5/local/1025/Aiobject-yolov5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o -c /home/tc-eb5/local/1025/Aiobject-yolov5/src/time_utility.cpp

CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tc-eb5/local/1025/Aiobject-yolov5/src/time_utility.cpp > CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.i

CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tc-eb5/local/1025/Aiobject-yolov5/src/time_utility.cpp -o CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.s

CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o.requires:

.PHONY : CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o.requires

CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o.provides: CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o.requires
	$(MAKE) -f CMakeFiles/AiObject-Yolov5.dir/build.make CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o.provides.build
.PHONY : CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o.provides

CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o.provides.build: CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o


CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o: CMakeFiles/AiObject-Yolov5.dir/flags.make
CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o: ../src/TS_YoloClassification.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tc-eb5/local/1025/Aiobject-yolov5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o -c /home/tc-eb5/local/1025/Aiobject-yolov5/src/TS_YoloClassification.cpp

CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tc-eb5/local/1025/Aiobject-yolov5/src/TS_YoloClassification.cpp > CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.i

CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tc-eb5/local/1025/Aiobject-yolov5/src/TS_YoloClassification.cpp -o CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.s

CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o.requires:

.PHONY : CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o.requires

CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o.provides: CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o.requires
	$(MAKE) -f CMakeFiles/AiObject-Yolov5.dir/build.make CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o.provides.build
.PHONY : CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o.provides

CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o.provides.build: CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o


CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o: CMakeFiles/AiObject-Yolov5.dir/flags.make
CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o: ../src/yolov5_detection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tc-eb5/local/1025/Aiobject-yolov5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o -c /home/tc-eb5/local/1025/Aiobject-yolov5/src/yolov5_detection.cpp

CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tc-eb5/local/1025/Aiobject-yolov5/src/yolov5_detection.cpp > CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.i

CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tc-eb5/local/1025/Aiobject-yolov5/src/yolov5_detection.cpp -o CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.s

CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o.requires:

.PHONY : CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o.requires

CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o.provides: CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o.requires
	$(MAKE) -f CMakeFiles/AiObject-Yolov5.dir/build.make CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o.provides.build
.PHONY : CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o.provides

CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o.provides.build: CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o


CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o: CMakeFiles/AiObject-Yolov5.dir/flags.make
CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o: ../src/TsCamera-rtmp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tc-eb5/local/1025/Aiobject-yolov5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o -c /home/tc-eb5/local/1025/Aiobject-yolov5/src/TsCamera-rtmp.cpp

CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tc-eb5/local/1025/Aiobject-yolov5/src/TsCamera-rtmp.cpp > CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.i

CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tc-eb5/local/1025/Aiobject-yolov5/src/TsCamera-rtmp.cpp -o CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.s

CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o.requires:

.PHONY : CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o.requires

CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o.provides: CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o.requires
	$(MAKE) -f CMakeFiles/AiObject-Yolov5.dir/build.make CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o.provides.build
.PHONY : CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o.provides

CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o.provides.build: CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o


# Object files for target AiObject-Yolov5
AiObject__Yolov5_OBJECTS = \
"CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o" \
"CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o" \
"CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o" \
"CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o"

# External object files for target AiObject-Yolov5
AiObject__Yolov5_EXTERNAL_OBJECTS =

AiObject-Yolov5: CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o
AiObject-Yolov5: CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o
AiObject-Yolov5: CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o
AiObject-Yolov5: CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o
AiObject-Yolov5: CMakeFiles/AiObject-Yolov5.dir/build.make
AiObject-Yolov5: ../libs/aarch/libSNPE.so
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_shape.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_stitching.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_superres.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_videostab.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_aruco.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_bgsegm.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_bioinspired.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_ccalib.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_datasets.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_dpm.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_face.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_freetype.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_fuzzy.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_hdf.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_line_descriptor.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_optflow.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_plot.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_reg.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_saliency.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_stereo.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_structured_light.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_surface_matching.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_text.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_ximgproc.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_xobjdetect.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_xphoto.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_video.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_viz.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_rgbd.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_calib3d.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_features2d.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_flann.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_objdetect.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_ml.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_highgui.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_photo.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_videoio.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_imgcodecs.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_imgproc.so.3.2.0
AiObject-Yolov5: /usr/lib/aarch64-linux-gnu/libopencv_core.so.3.2.0
AiObject-Yolov5: CMakeFiles/AiObject-Yolov5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tc-eb5/local/1025/Aiobject-yolov5/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable AiObject-Yolov5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AiObject-Yolov5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AiObject-Yolov5.dir/build: AiObject-Yolov5

.PHONY : CMakeFiles/AiObject-Yolov5.dir/build

CMakeFiles/AiObject-Yolov5.dir/requires: CMakeFiles/AiObject-Yolov5.dir/src/time_utility.cpp.o.requires
CMakeFiles/AiObject-Yolov5.dir/requires: CMakeFiles/AiObject-Yolov5.dir/src/TS_YoloClassification.cpp.o.requires
CMakeFiles/AiObject-Yolov5.dir/requires: CMakeFiles/AiObject-Yolov5.dir/src/yolov5_detection.cpp.o.requires
CMakeFiles/AiObject-Yolov5.dir/requires: CMakeFiles/AiObject-Yolov5.dir/src/TsCamera-rtmp.cpp.o.requires

.PHONY : CMakeFiles/AiObject-Yolov5.dir/requires

CMakeFiles/AiObject-Yolov5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AiObject-Yolov5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AiObject-Yolov5.dir/clean

CMakeFiles/AiObject-Yolov5.dir/depend:
	cd /home/tc-eb5/local/1025/Aiobject-yolov5/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tc-eb5/local/1025/Aiobject-yolov5 /home/tc-eb5/local/1025/Aiobject-yolov5 /home/tc-eb5/local/1025/Aiobject-yolov5/build /home/tc-eb5/local/1025/Aiobject-yolov5/build /home/tc-eb5/local/1025/Aiobject-yolov5/build/CMakeFiles/AiObject-Yolov5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/AiObject-Yolov5.dir/depend

