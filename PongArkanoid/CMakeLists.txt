cmake_minimum_required(VERSION 2.8.11)
project(PongArkanoid)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/CMake/)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


file(GLOB SOURCE "game/*.cpp" "game/*.cc" "game/*.h")

find_package(SDL2 REQUIRED)

include_directories(PongArkanoid 
                                ${SDL2_INCLUDE_DIRS})

add_executable(PongArkanoid ${SOURCE})

target_link_libraries(PongArkanoid 
                                ${SDL2_LIBRARIES}) 