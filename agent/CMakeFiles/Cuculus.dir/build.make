# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yangrk/Cuculus/agent

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yangrk/Cuculus/agent

# Include any dependencies generated for this target.
include CMakeFiles/Cuculus.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Cuculus.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Cuculus.dir/flags.make

CMakeFiles/Cuculus.dir/TaskThread.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/TaskThread.cpp.o: TaskThread.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/TaskThread.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/TaskThread.cpp.o -c /home/yangrk/Cuculus/agent/TaskThread.cpp

CMakeFiles/Cuculus.dir/TaskThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/TaskThread.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/agent/TaskThread.cpp > CMakeFiles/Cuculus.dir/TaskThread.cpp.i

CMakeFiles/Cuculus.dir/TaskThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/TaskThread.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/agent/TaskThread.cpp -o CMakeFiles/Cuculus.dir/TaskThread.cpp.s

CMakeFiles/Cuculus.dir/TaskThread.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/TaskThread.cpp.o.requires

CMakeFiles/Cuculus.dir/TaskThread.cpp.o.provides: CMakeFiles/Cuculus.dir/TaskThread.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/TaskThread.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/TaskThread.cpp.o.provides

CMakeFiles/Cuculus.dir/TaskThread.cpp.o.provides.build: CMakeFiles/Cuculus.dir/TaskThread.cpp.o

CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o: CuculusTimer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o -c /home/yangrk/Cuculus/agent/CuculusTimer.cpp

CMakeFiles/Cuculus.dir/CuculusTimer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/CuculusTimer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/agent/CuculusTimer.cpp > CMakeFiles/Cuculus.dir/CuculusTimer.cpp.i

CMakeFiles/Cuculus.dir/CuculusTimer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/CuculusTimer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/agent/CuculusTimer.cpp -o CMakeFiles/Cuculus.dir/CuculusTimer.cpp.s

CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o.requires

CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o.provides: CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o.provides

CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o.provides.build: CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o

CMakeFiles/Cuculus.dir/main.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/main.cpp.o: main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/main.cpp.o -c /home/yangrk/Cuculus/agent/main.cpp

CMakeFiles/Cuculus.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/agent/main.cpp > CMakeFiles/Cuculus.dir/main.cpp.i

CMakeFiles/Cuculus.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/agent/main.cpp -o CMakeFiles/Cuculus.dir/main.cpp.s

CMakeFiles/Cuculus.dir/main.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/main.cpp.o.requires

CMakeFiles/Cuculus.dir/main.cpp.o.provides: CMakeFiles/Cuculus.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/main.cpp.o.provides

CMakeFiles/Cuculus.dir/main.cpp.o.provides.build: CMakeFiles/Cuculus.dir/main.cpp.o

CMakeFiles/Cuculus.dir/Work.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/Work.cpp.o: Work.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/Work.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/Work.cpp.o -c /home/yangrk/Cuculus/agent/Work.cpp

CMakeFiles/Cuculus.dir/Work.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/Work.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/agent/Work.cpp > CMakeFiles/Cuculus.dir/Work.cpp.i

CMakeFiles/Cuculus.dir/Work.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/Work.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/agent/Work.cpp -o CMakeFiles/Cuculus.dir/Work.cpp.s

CMakeFiles/Cuculus.dir/Work.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/Work.cpp.o.requires

CMakeFiles/Cuculus.dir/Work.cpp.o.provides: CMakeFiles/Cuculus.dir/Work.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/Work.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/Work.cpp.o.provides

CMakeFiles/Cuculus.dir/Work.cpp.o.provides.build: CMakeFiles/Cuculus.dir/Work.cpp.o

CMakeFiles/Cuculus.dir/YearWork.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/YearWork.cpp.o: YearWork.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/YearWork.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/YearWork.cpp.o -c /home/yangrk/Cuculus/agent/YearWork.cpp

CMakeFiles/Cuculus.dir/YearWork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/YearWork.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/agent/YearWork.cpp > CMakeFiles/Cuculus.dir/YearWork.cpp.i

CMakeFiles/Cuculus.dir/YearWork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/YearWork.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/agent/YearWork.cpp -o CMakeFiles/Cuculus.dir/YearWork.cpp.s

CMakeFiles/Cuculus.dir/YearWork.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/YearWork.cpp.o.requires

CMakeFiles/Cuculus.dir/YearWork.cpp.o.provides: CMakeFiles/Cuculus.dir/YearWork.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/YearWork.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/YearWork.cpp.o.provides

CMakeFiles/Cuculus.dir/YearWork.cpp.o.provides.build: CMakeFiles/Cuculus.dir/YearWork.cpp.o

CMakeFiles/Cuculus.dir/ConfSock.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/ConfSock.cpp.o: ConfSock.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/ConfSock.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/ConfSock.cpp.o -c /home/yangrk/Cuculus/agent/ConfSock.cpp

CMakeFiles/Cuculus.dir/ConfSock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/ConfSock.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/agent/ConfSock.cpp > CMakeFiles/Cuculus.dir/ConfSock.cpp.i

CMakeFiles/Cuculus.dir/ConfSock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/ConfSock.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/agent/ConfSock.cpp -o CMakeFiles/Cuculus.dir/ConfSock.cpp.s

CMakeFiles/Cuculus.dir/ConfSock.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/ConfSock.cpp.o.requires

CMakeFiles/Cuculus.dir/ConfSock.cpp.o.provides: CMakeFiles/Cuculus.dir/ConfSock.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/ConfSock.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/ConfSock.cpp.o.provides

CMakeFiles/Cuculus.dir/ConfSock.cpp.o.provides.build: CMakeFiles/Cuculus.dir/ConfSock.cpp.o

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o: /home/yangrk/Cuculus/PLib/Logger_impl.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o -c /home/yangrk/Cuculus/PLib/Logger_impl.cpp

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/PLib/Logger_impl.cpp > CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.i

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/PLib/Logger_impl.cpp -o CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.s

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o.requires

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o.provides: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o.provides

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o.provides.build: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o: /home/yangrk/Cuculus/PLib/IniFile.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o -c /home/yangrk/Cuculus/PLib/IniFile.cpp

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/PLib/IniFile.cpp > CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.i

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/PLib/IniFile.cpp -o CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.s

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o.requires

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o.provides: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o.provides

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o.provides.build: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o: CMakeFiles/Cuculus.dir/flags.make
CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o: /home/yangrk/Cuculus/PLib/Logger.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yangrk/Cuculus/agent/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o -c /home/yangrk/Cuculus/PLib/Logger.cpp

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yangrk/Cuculus/PLib/Logger.cpp > CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.i

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yangrk/Cuculus/PLib/Logger.cpp -o CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.s

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o.requires:
.PHONY : CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o.requires

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o.provides: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o.requires
	$(MAKE) -f CMakeFiles/Cuculus.dir/build.make CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o.provides.build
.PHONY : CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o.provides

CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o.provides.build: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o

# Object files for target Cuculus
Cuculus_OBJECTS = \
"CMakeFiles/Cuculus.dir/TaskThread.cpp.o" \
"CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o" \
"CMakeFiles/Cuculus.dir/main.cpp.o" \
"CMakeFiles/Cuculus.dir/Work.cpp.o" \
"CMakeFiles/Cuculus.dir/YearWork.cpp.o" \
"CMakeFiles/Cuculus.dir/ConfSock.cpp.o" \
"CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o" \
"CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o" \
"CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o"

# External object files for target Cuculus
Cuculus_EXTERNAL_OBJECTS =

Cuculus: CMakeFiles/Cuculus.dir/TaskThread.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/main.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/Work.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/YearWork.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/ConfSock.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o
Cuculus: CMakeFiles/Cuculus.dir/build.make
Cuculus: CMakeFiles/Cuculus.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Cuculus"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Cuculus.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Cuculus.dir/build: Cuculus
.PHONY : CMakeFiles/Cuculus.dir/build

CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/TaskThread.cpp.o.requires
CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/CuculusTimer.cpp.o.requires
CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/main.cpp.o.requires
CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/Work.cpp.o.requires
CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/YearWork.cpp.o.requires
CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/ConfSock.cpp.o.requires
CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger_impl.cpp.o.requires
CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/IniFile.cpp.o.requires
CMakeFiles/Cuculus.dir/requires: CMakeFiles/Cuculus.dir/home/yangrk/Cuculus/PLib/Logger.cpp.o.requires
.PHONY : CMakeFiles/Cuculus.dir/requires

CMakeFiles/Cuculus.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Cuculus.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Cuculus.dir/clean

CMakeFiles/Cuculus.dir/depend:
	cd /home/yangrk/Cuculus/agent && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yangrk/Cuculus/agent /home/yangrk/Cuculus/agent /home/yangrk/Cuculus/agent /home/yangrk/Cuculus/agent /home/yangrk/Cuculus/agent/CMakeFiles/Cuculus.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Cuculus.dir/depend

