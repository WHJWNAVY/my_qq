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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/work/my_program/my_qq

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/work/my_program/my_qq/build

# Include any dependencies generated for this target.
include qq_client/CMakeFiles/client_qq.dir/depend.make

# Include the progress variables for this target.
include qq_client/CMakeFiles/client_qq.dir/progress.make

# Include the compile flags for this target's objects.
include qq_client/CMakeFiles/client_qq.dir/flags.make

qq_client/CMakeFiles/client_qq.dir/qq_client.c.o: qq_client/CMakeFiles/client_qq.dir/flags.make
qq_client/CMakeFiles/client_qq.dir/qq_client.c.o: ../qq_client/qq_client.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/my_program/my_qq/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object qq_client/CMakeFiles/client_qq.dir/qq_client.c.o"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/client_qq.dir/qq_client.c.o   -c /home/work/my_program/my_qq/qq_client/qq_client.c

qq_client/CMakeFiles/client_qq.dir/qq_client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_qq.dir/qq_client.c.i"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/my_program/my_qq/qq_client/qq_client.c > CMakeFiles/client_qq.dir/qq_client.c.i

qq_client/CMakeFiles/client_qq.dir/qq_client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_qq.dir/qq_client.c.s"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/my_program/my_qq/qq_client/qq_client.c -o CMakeFiles/client_qq.dir/qq_client.c.s

qq_client/CMakeFiles/client_qq.dir/qq_client.c.o.requires:
.PHONY : qq_client/CMakeFiles/client_qq.dir/qq_client.c.o.requires

qq_client/CMakeFiles/client_qq.dir/qq_client.c.o.provides: qq_client/CMakeFiles/client_qq.dir/qq_client.c.o.requires
	$(MAKE) -f qq_client/CMakeFiles/client_qq.dir/build.make qq_client/CMakeFiles/client_qq.dir/qq_client.c.o.provides.build
.PHONY : qq_client/CMakeFiles/client_qq.dir/qq_client.c.o.provides

qq_client/CMakeFiles/client_qq.dir/qq_client.c.o.provides.build: qq_client/CMakeFiles/client_qq.dir/qq_client.c.o

qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o: qq_client/CMakeFiles/client_qq.dir/flags.make
qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o: ../my_utils/main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/my_program/my_qq/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/client_qq.dir/__/my_utils/main.c.o   -c /home/work/my_program/my_qq/my_utils/main.c

qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_qq.dir/__/my_utils/main.c.i"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/my_program/my_qq/my_utils/main.c > CMakeFiles/client_qq.dir/__/my_utils/main.c.i

qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_qq.dir/__/my_utils/main.c.s"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/my_program/my_qq/my_utils/main.c -o CMakeFiles/client_qq.dir/__/my_utils/main.c.s

qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o.requires:
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o.requires

qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o.provides: qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o.requires
	$(MAKE) -f qq_client/CMakeFiles/client_qq.dir/build.make qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o.provides.build
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o.provides

qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o.provides.build: qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o

qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o: qq_client/CMakeFiles/client_qq.dir/flags.make
qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o: ../my_utils/my_socket.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/my_program/my_qq/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o   -c /home/work/my_program/my_qq/my_utils/my_socket.c

qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.i"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/my_program/my_qq/my_utils/my_socket.c > CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.i

qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.s"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/my_program/my_qq/my_utils/my_socket.c -o CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.s

qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o.requires:
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o.requires

qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o.provides: qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o.requires
	$(MAKE) -f qq_client/CMakeFiles/client_qq.dir/build.make qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o.provides.build
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o.provides

qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o.provides.build: qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o

qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o: qq_client/CMakeFiles/client_qq.dir/flags.make
qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o: ../my_utils/readline.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/my_program/my_qq/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/client_qq.dir/__/my_utils/readline.c.o   -c /home/work/my_program/my_qq/my_utils/readline.c

qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_qq.dir/__/my_utils/readline.c.i"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/my_program/my_qq/my_utils/readline.c > CMakeFiles/client_qq.dir/__/my_utils/readline.c.i

qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_qq.dir/__/my_utils/readline.c.s"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/my_program/my_qq/my_utils/readline.c -o CMakeFiles/client_qq.dir/__/my_utils/readline.c.s

qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o.requires:
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o.requires

qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o.provides: qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o.requires
	$(MAKE) -f qq_client/CMakeFiles/client_qq.dir/build.make qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o.provides.build
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o.provides

qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o.provides.build: qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o

qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o: qq_client/CMakeFiles/client_qq.dir/flags.make
qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o: ../my_utils/shell_cmd.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/my_program/my_qq/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o   -c /home/work/my_program/my_qq/my_utils/shell_cmd.c

qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.i"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/my_program/my_qq/my_utils/shell_cmd.c > CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.i

qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.s"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/my_program/my_qq/my_utils/shell_cmd.c -o CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.s

qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o.requires:
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o.requires

qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o.provides: qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o.requires
	$(MAKE) -f qq_client/CMakeFiles/client_qq.dir/build.make qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o.provides.build
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o.provides

qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o.provides.build: qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o

qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o: qq_client/CMakeFiles/client_qq.dir/flags.make
qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o: ../my_utils/qq_msg.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/work/my_program/my_qq/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o   -c /home/work/my_program/my_qq/my_utils/qq_msg.c

qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.i"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /home/work/my_program/my_qq/my_utils/qq_msg.c > CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.i

qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.s"
	cd /home/work/my_program/my_qq/build/qq_client && /usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /home/work/my_program/my_qq/my_utils/qq_msg.c -o CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.s

qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o.requires:
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o.requires

qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o.provides: qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o.requires
	$(MAKE) -f qq_client/CMakeFiles/client_qq.dir/build.make qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o.provides.build
.PHONY : qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o.provides

qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o.provides.build: qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o

# Object files for target client_qq
client_qq_OBJECTS = \
"CMakeFiles/client_qq.dir/qq_client.c.o" \
"CMakeFiles/client_qq.dir/__/my_utils/main.c.o" \
"CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o" \
"CMakeFiles/client_qq.dir/__/my_utils/readline.c.o" \
"CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o" \
"CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o"

# External object files for target client_qq
client_qq_EXTERNAL_OBJECTS =

qq_client/client_qq: qq_client/CMakeFiles/client_qq.dir/qq_client.c.o
qq_client/client_qq: qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o
qq_client/client_qq: qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o
qq_client/client_qq: qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o
qq_client/client_qq: qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o
qq_client/client_qq: qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o
qq_client/client_qq: qq_client/CMakeFiles/client_qq.dir/build.make
qq_client/client_qq: qq_client/CMakeFiles/client_qq.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable client_qq"
	cd /home/work/my_program/my_qq/build/qq_client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client_qq.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
qq_client/CMakeFiles/client_qq.dir/build: qq_client/client_qq
.PHONY : qq_client/CMakeFiles/client_qq.dir/build

qq_client/CMakeFiles/client_qq.dir/requires: qq_client/CMakeFiles/client_qq.dir/qq_client.c.o.requires
qq_client/CMakeFiles/client_qq.dir/requires: qq_client/CMakeFiles/client_qq.dir/__/my_utils/main.c.o.requires
qq_client/CMakeFiles/client_qq.dir/requires: qq_client/CMakeFiles/client_qq.dir/__/my_utils/my_socket.c.o.requires
qq_client/CMakeFiles/client_qq.dir/requires: qq_client/CMakeFiles/client_qq.dir/__/my_utils/readline.c.o.requires
qq_client/CMakeFiles/client_qq.dir/requires: qq_client/CMakeFiles/client_qq.dir/__/my_utils/shell_cmd.c.o.requires
qq_client/CMakeFiles/client_qq.dir/requires: qq_client/CMakeFiles/client_qq.dir/__/my_utils/qq_msg.c.o.requires
.PHONY : qq_client/CMakeFiles/client_qq.dir/requires

qq_client/CMakeFiles/client_qq.dir/clean:
	cd /home/work/my_program/my_qq/build/qq_client && $(CMAKE_COMMAND) -P CMakeFiles/client_qq.dir/cmake_clean.cmake
.PHONY : qq_client/CMakeFiles/client_qq.dir/clean

qq_client/CMakeFiles/client_qq.dir/depend:
	cd /home/work/my_program/my_qq/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/work/my_program/my_qq /home/work/my_program/my_qq/qq_client /home/work/my_program/my_qq/build /home/work/my_program/my_qq/build/qq_client /home/work/my_program/my_qq/build/qq_client/CMakeFiles/client_qq.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : qq_client/CMakeFiles/client_qq.dir/depend

