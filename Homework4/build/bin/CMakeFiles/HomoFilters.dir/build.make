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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/quasi/BME_Image_Processing/Homework4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/quasi/BME_Image_Processing/Homework4/build

# Include any dependencies generated for this target.
include bin/CMakeFiles/HomoFilters.dir/depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/HomoFilters.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/HomoFilters.dir/flags.make

bin/CMakeFiles/HomoFilters.dir/HomoFilters.cpp.o: bin/CMakeFiles/HomoFilters.dir/flags.make
bin/CMakeFiles/HomoFilters.dir/HomoFilters.cpp.o: ../src/HomoFilters.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/quasi/BME_Image_Processing/Homework4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/CMakeFiles/HomoFilters.dir/HomoFilters.cpp.o"
	cd /home/quasi/BME_Image_Processing/Homework4/build/bin && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HomoFilters.dir/HomoFilters.cpp.o -c /home/quasi/BME_Image_Processing/Homework4/src/HomoFilters.cpp

bin/CMakeFiles/HomoFilters.dir/HomoFilters.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HomoFilters.dir/HomoFilters.cpp.i"
	cd /home/quasi/BME_Image_Processing/Homework4/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/quasi/BME_Image_Processing/Homework4/src/HomoFilters.cpp > CMakeFiles/HomoFilters.dir/HomoFilters.cpp.i

bin/CMakeFiles/HomoFilters.dir/HomoFilters.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HomoFilters.dir/HomoFilters.cpp.s"
	cd /home/quasi/BME_Image_Processing/Homework4/build/bin && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/quasi/BME_Image_Processing/Homework4/src/HomoFilters.cpp -o CMakeFiles/HomoFilters.dir/HomoFilters.cpp.s

# Object files for target HomoFilters
HomoFilters_OBJECTS = \
"CMakeFiles/HomoFilters.dir/HomoFilters.cpp.o"

# External object files for target HomoFilters
HomoFilters_EXTERNAL_OBJECTS =

bin/HomoFilters: bin/CMakeFiles/HomoFilters.dir/HomoFilters.cpp.o
bin/HomoFilters: bin/CMakeFiles/HomoFilters.dir/build.make
bin/HomoFilters: /usr/local/lib/libopencv_stitching.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_gapi.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_xobjdetect.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_superres.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_xphoto.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_hfs.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_surface_matching.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_tracking.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_rgbd.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_xfeatures2d.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_dpm.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_line_descriptor.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_datasets.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_face.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_reg.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_fuzzy.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_bioinspired.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_bgsegm.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_structured_light.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_optflow.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_saliency.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_freetype.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_phase_unwrapping.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_img_hash.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_plot.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_aruco.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_hdf.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_videostab.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_ximgproc.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_stereo.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_ccalib.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_shape.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_ml.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_objdetect.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_photo.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_video.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_calib3d.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_features2d.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_flann.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_highgui.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_videoio.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_imgcodecs.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_imgproc.so.4.0.1
bin/HomoFilters: /usr/local/lib/libopencv_core.so.4.0.1
bin/HomoFilters: bin/CMakeFiles/HomoFilters.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/quasi/BME_Image_Processing/Homework4/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HomoFilters"
	cd /home/quasi/BME_Image_Processing/Homework4/build/bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HomoFilters.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/HomoFilters.dir/build: bin/HomoFilters

.PHONY : bin/CMakeFiles/HomoFilters.dir/build

bin/CMakeFiles/HomoFilters.dir/clean:
	cd /home/quasi/BME_Image_Processing/Homework4/build/bin && $(CMAKE_COMMAND) -P CMakeFiles/HomoFilters.dir/cmake_clean.cmake
.PHONY : bin/CMakeFiles/HomoFilters.dir/clean

bin/CMakeFiles/HomoFilters.dir/depend:
	cd /home/quasi/BME_Image_Processing/Homework4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/quasi/BME_Image_Processing/Homework4 /home/quasi/BME_Image_Processing/Homework4/src /home/quasi/BME_Image_Processing/Homework4/build /home/quasi/BME_Image_Processing/Homework4/build/bin /home/quasi/BME_Image_Processing/Homework4/build/bin/CMakeFiles/HomoFilters.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bin/CMakeFiles/HomoFilters.dir/depend

