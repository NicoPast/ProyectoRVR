# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build

# Include any dependencies generated for this target.
include CMakeFiles/PongArkanoid.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PongArkanoid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PongArkanoid.dir/flags.make

CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.o: ../game/Bullet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Bullet.cpp

CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Bullet.cpp > CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.i

CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Bullet.cpp -o CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.s

CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.o: ../game/GameMessage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/GameMessage.cpp

CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/GameMessage.cpp > CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.i

CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/GameMessage.cpp -o CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.s

CMakeFiles/PongArkanoid.dir/game/Logic.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/Logic.cpp.o: ../game/Logic.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PongArkanoid.dir/game/Logic.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/Logic.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Logic.cpp

CMakeFiles/PongArkanoid.dir/game/Logic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/Logic.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Logic.cpp > CMakeFiles/PongArkanoid.dir/game/Logic.cpp.i

CMakeFiles/PongArkanoid.dir/game/Logic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/Logic.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Logic.cpp -o CMakeFiles/PongArkanoid.dir/game/Logic.cpp.s

CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.o: ../game/NetClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/NetClient.cpp

CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/NetClient.cpp > CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.i

CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/NetClient.cpp -o CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.s

CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.o: ../game/NetServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/NetServer.cpp

CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/NetServer.cpp > CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.i

CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/NetServer.cpp -o CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.s

CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.o: ../game/Paddle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Paddle.cpp

CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Paddle.cpp > CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.i

CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Paddle.cpp -o CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.s

CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.o: ../game/SDLGame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/SDLGame.cpp

CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/SDLGame.cpp > CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.i

CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/SDLGame.cpp -o CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.s

CMakeFiles/PongArkanoid.dir/game/Socket.cc.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/Socket.cc.o: ../game/Socket.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/PongArkanoid.dir/game/Socket.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/Socket.cc.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Socket.cc

CMakeFiles/PongArkanoid.dir/game/Socket.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/Socket.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Socket.cc > CMakeFiles/PongArkanoid.dir/game/Socket.cc.i

CMakeFiles/PongArkanoid.dir/game/Socket.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/Socket.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Socket.cc -o CMakeFiles/PongArkanoid.dir/game/Socket.cc.s

CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.o: ../game/Vector2D.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Vector2D.cpp

CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Vector2D.cpp > CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.i

CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/Vector2D.cpp -o CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.s

CMakeFiles/PongArkanoid.dir/game/main.cpp.o: CMakeFiles/PongArkanoid.dir/flags.make
CMakeFiles/PongArkanoid.dir/game/main.cpp.o: ../game/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/PongArkanoid.dir/game/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PongArkanoid.dir/game/main.cpp.o -c /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/main.cpp

CMakeFiles/PongArkanoid.dir/game/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PongArkanoid.dir/game/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/main.cpp > CMakeFiles/PongArkanoid.dir/game/main.cpp.i

CMakeFiles/PongArkanoid.dir/game/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PongArkanoid.dir/game/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/game/main.cpp -o CMakeFiles/PongArkanoid.dir/game/main.cpp.s

# Object files for target PongArkanoid
PongArkanoid_OBJECTS = \
"CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.o" \
"CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.o" \
"CMakeFiles/PongArkanoid.dir/game/Logic.cpp.o" \
"CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.o" \
"CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.o" \
"CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.o" \
"CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.o" \
"CMakeFiles/PongArkanoid.dir/game/Socket.cc.o" \
"CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.o" \
"CMakeFiles/PongArkanoid.dir/game/main.cpp.o"

# External object files for target PongArkanoid
PongArkanoid_EXTERNAL_OBJECTS =

PongArkanoid: CMakeFiles/PongArkanoid.dir/game/Bullet.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/GameMessage.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/Logic.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/NetClient.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/NetServer.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/Paddle.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/SDLGame.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/Socket.cc.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/Vector2D.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/game/main.cpp.o
PongArkanoid: CMakeFiles/PongArkanoid.dir/build.make
PongArkanoid: /usr/lib/x86_64-linux-gnu/libSDL2_image.so
PongArkanoid: /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so
PongArkanoid: /usr/lib/x86_64-linux-gnu/libSDL2_net.so
PongArkanoid: /usr/lib/x86_64-linux-gnu/libSDL2_mixer.so
PongArkanoid: CMakeFiles/PongArkanoid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable PongArkanoid"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PongArkanoid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PongArkanoid.dir/build: PongArkanoid

.PHONY : CMakeFiles/PongArkanoid.dir/build

CMakeFiles/PongArkanoid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PongArkanoid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PongArkanoid.dir/clean

CMakeFiles/PongArkanoid.dir/depend:
	cd /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build /home/usuarioso/Desktop/ProyectoRVR/ProyectoRVR/PongArkanoid/build/CMakeFiles/PongArkanoid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PongArkanoid.dir/depend

