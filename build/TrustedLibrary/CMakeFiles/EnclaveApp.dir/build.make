# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_SOURCE_DIR = /home/ywl/Documents/sgx-template

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ywl/Documents/sgx-template/build

# Include any dependencies generated for this target.
include TrustedLibrary/CMakeFiles/EnclaveApp.dir/depend.make

# Include the progress variables for this target.
include TrustedLibrary/CMakeFiles/EnclaveApp.dir/progress.make

# Include the compile flags for this target's objects.
include TrustedLibrary/CMakeFiles/EnclaveApp.dir/flags.make

TrustedLibrary/Enclave_u.h:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/ywl/Documents/sgx-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "make ucode"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /opt/intel/sgxsdk/bin/x64/sgx_edger8r --untrusted /home/ywl/Documents/sgx-template/Enclave/Enclave.edl --search-path /home/ywl/Documents/sgx-template/Enclave --search-path /opt/intel/sgxsdk/include --search-path /opt/intel/sgxssl/include

TrustedLibrary/Enclave_u.c: TrustedLibrary/Enclave_u.h
	@$(CMAKE_COMMAND) -E touch_nocreate TrustedLibrary/Enclave_u.c

TrustedLibrary/CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.o: TrustedLibrary/CMakeFiles/EnclaveApp.dir/flags.make
TrustedLibrary/CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.o: ../TrustedLibrary/EnclaveApp.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywl/Documents/sgx-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object TrustedLibrary/CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.o"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.o -c /home/ywl/Documents/sgx-template/TrustedLibrary/EnclaveApp.cpp

TrustedLibrary/CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.i"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywl/Documents/sgx-template/TrustedLibrary/EnclaveApp.cpp > CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.i

TrustedLibrary/CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.s"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywl/Documents/sgx-template/TrustedLibrary/EnclaveApp.cpp -o CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.s

TrustedLibrary/CMakeFiles/EnclaveApp.dir/common.cpp.o: TrustedLibrary/CMakeFiles/EnclaveApp.dir/flags.make
TrustedLibrary/CMakeFiles/EnclaveApp.dir/common.cpp.o: ../TrustedLibrary/common.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywl/Documents/sgx-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object TrustedLibrary/CMakeFiles/EnclaveApp.dir/common.cpp.o"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EnclaveApp.dir/common.cpp.o -c /home/ywl/Documents/sgx-template/TrustedLibrary/common.cpp

TrustedLibrary/CMakeFiles/EnclaveApp.dir/common.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EnclaveApp.dir/common.cpp.i"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywl/Documents/sgx-template/TrustedLibrary/common.cpp > CMakeFiles/EnclaveApp.dir/common.cpp.i

TrustedLibrary/CMakeFiles/EnclaveApp.dir/common.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EnclaveApp.dir/common.cpp.s"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywl/Documents/sgx-template/TrustedLibrary/common.cpp -o CMakeFiles/EnclaveApp.dir/common.cpp.s

TrustedLibrary/CMakeFiles/EnclaveApp.dir/easylogging++.cpp.o: TrustedLibrary/CMakeFiles/EnclaveApp.dir/flags.make
TrustedLibrary/CMakeFiles/EnclaveApp.dir/easylogging++.cpp.o: ../TrustedLibrary/easylogging++.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywl/Documents/sgx-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object TrustedLibrary/CMakeFiles/EnclaveApp.dir/easylogging++.cpp.o"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EnclaveApp.dir/easylogging++.cpp.o -c /home/ywl/Documents/sgx-template/TrustedLibrary/easylogging++.cpp

TrustedLibrary/CMakeFiles/EnclaveApp.dir/easylogging++.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EnclaveApp.dir/easylogging++.cpp.i"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywl/Documents/sgx-template/TrustedLibrary/easylogging++.cpp > CMakeFiles/EnclaveApp.dir/easylogging++.cpp.i

TrustedLibrary/CMakeFiles/EnclaveApp.dir/easylogging++.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EnclaveApp.dir/easylogging++.cpp.s"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywl/Documents/sgx-template/TrustedLibrary/easylogging++.cpp -o CMakeFiles/EnclaveApp.dir/easylogging++.cpp.s

TrustedLibrary/CMakeFiles/EnclaveApp.dir/ecalls.cpp.o: TrustedLibrary/CMakeFiles/EnclaveApp.dir/flags.make
TrustedLibrary/CMakeFiles/EnclaveApp.dir/ecalls.cpp.o: ../TrustedLibrary/ecalls.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywl/Documents/sgx-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object TrustedLibrary/CMakeFiles/EnclaveApp.dir/ecalls.cpp.o"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EnclaveApp.dir/ecalls.cpp.o -c /home/ywl/Documents/sgx-template/TrustedLibrary/ecalls.cpp

TrustedLibrary/CMakeFiles/EnclaveApp.dir/ecalls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EnclaveApp.dir/ecalls.cpp.i"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywl/Documents/sgx-template/TrustedLibrary/ecalls.cpp > CMakeFiles/EnclaveApp.dir/ecalls.cpp.i

TrustedLibrary/CMakeFiles/EnclaveApp.dir/ecalls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EnclaveApp.dir/ecalls.cpp.s"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywl/Documents/sgx-template/TrustedLibrary/ecalls.cpp -o CMakeFiles/EnclaveApp.dir/ecalls.cpp.s

TrustedLibrary/CMakeFiles/EnclaveApp.dir/ocalls.cpp.o: TrustedLibrary/CMakeFiles/EnclaveApp.dir/flags.make
TrustedLibrary/CMakeFiles/EnclaveApp.dir/ocalls.cpp.o: ../TrustedLibrary/ocalls.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywl/Documents/sgx-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object TrustedLibrary/CMakeFiles/EnclaveApp.dir/ocalls.cpp.o"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/EnclaveApp.dir/ocalls.cpp.o -c /home/ywl/Documents/sgx-template/TrustedLibrary/ocalls.cpp

TrustedLibrary/CMakeFiles/EnclaveApp.dir/ocalls.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/EnclaveApp.dir/ocalls.cpp.i"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ywl/Documents/sgx-template/TrustedLibrary/ocalls.cpp > CMakeFiles/EnclaveApp.dir/ocalls.cpp.i

TrustedLibrary/CMakeFiles/EnclaveApp.dir/ocalls.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/EnclaveApp.dir/ocalls.cpp.s"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ywl/Documents/sgx-template/TrustedLibrary/ocalls.cpp -o CMakeFiles/EnclaveApp.dir/ocalls.cpp.s

TrustedLibrary/CMakeFiles/EnclaveApp.dir/Enclave_u.c.o: TrustedLibrary/CMakeFiles/EnclaveApp.dir/flags.make
TrustedLibrary/CMakeFiles/EnclaveApp.dir/Enclave_u.c.o: TrustedLibrary/Enclave_u.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ywl/Documents/sgx-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object TrustedLibrary/CMakeFiles/EnclaveApp.dir/Enclave_u.c.o"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/EnclaveApp.dir/Enclave_u.c.o   -c /home/ywl/Documents/sgx-template/build/TrustedLibrary/Enclave_u.c

TrustedLibrary/CMakeFiles/EnclaveApp.dir/Enclave_u.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/EnclaveApp.dir/Enclave_u.c.i"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ywl/Documents/sgx-template/build/TrustedLibrary/Enclave_u.c > CMakeFiles/EnclaveApp.dir/Enclave_u.c.i

TrustedLibrary/CMakeFiles/EnclaveApp.dir/Enclave_u.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/EnclaveApp.dir/Enclave_u.c.s"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ywl/Documents/sgx-template/build/TrustedLibrary/Enclave_u.c -o CMakeFiles/EnclaveApp.dir/Enclave_u.c.s

# Object files for target EnclaveApp
EnclaveApp_OBJECTS = \
"CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.o" \
"CMakeFiles/EnclaveApp.dir/common.cpp.o" \
"CMakeFiles/EnclaveApp.dir/easylogging++.cpp.o" \
"CMakeFiles/EnclaveApp.dir/ecalls.cpp.o" \
"CMakeFiles/EnclaveApp.dir/ocalls.cpp.o" \
"CMakeFiles/EnclaveApp.dir/Enclave_u.c.o"

# External object files for target EnclaveApp
EnclaveApp_EXTERNAL_OBJECTS =

TrustedLibrary/libEnclaveApp.so: TrustedLibrary/CMakeFiles/EnclaveApp.dir/EnclaveApp.cpp.o
TrustedLibrary/libEnclaveApp.so: TrustedLibrary/CMakeFiles/EnclaveApp.dir/common.cpp.o
TrustedLibrary/libEnclaveApp.so: TrustedLibrary/CMakeFiles/EnclaveApp.dir/easylogging++.cpp.o
TrustedLibrary/libEnclaveApp.so: TrustedLibrary/CMakeFiles/EnclaveApp.dir/ecalls.cpp.o
TrustedLibrary/libEnclaveApp.so: TrustedLibrary/CMakeFiles/EnclaveApp.dir/ocalls.cpp.o
TrustedLibrary/libEnclaveApp.so: TrustedLibrary/CMakeFiles/EnclaveApp.dir/Enclave_u.c.o
TrustedLibrary/libEnclaveApp.so: TrustedLibrary/CMakeFiles/EnclaveApp.dir/build.make
TrustedLibrary/libEnclaveApp.so: TrustedLibrary/CMakeFiles/EnclaveApp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ywl/Documents/sgx-template/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX shared library libEnclaveApp.so"
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/EnclaveApp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
TrustedLibrary/CMakeFiles/EnclaveApp.dir/build: TrustedLibrary/libEnclaveApp.so

.PHONY : TrustedLibrary/CMakeFiles/EnclaveApp.dir/build

TrustedLibrary/CMakeFiles/EnclaveApp.dir/clean:
	cd /home/ywl/Documents/sgx-template/build/TrustedLibrary && $(CMAKE_COMMAND) -P CMakeFiles/EnclaveApp.dir/cmake_clean.cmake
.PHONY : TrustedLibrary/CMakeFiles/EnclaveApp.dir/clean

TrustedLibrary/CMakeFiles/EnclaveApp.dir/depend: TrustedLibrary/Enclave_u.h
TrustedLibrary/CMakeFiles/EnclaveApp.dir/depend: TrustedLibrary/Enclave_u.c
	cd /home/ywl/Documents/sgx-template/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ywl/Documents/sgx-template /home/ywl/Documents/sgx-template/TrustedLibrary /home/ywl/Documents/sgx-template/build /home/ywl/Documents/sgx-template/build/TrustedLibrary /home/ywl/Documents/sgx-template/build/TrustedLibrary/CMakeFiles/EnclaveApp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : TrustedLibrary/CMakeFiles/EnclaveApp.dir/depend

