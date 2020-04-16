cmake_minimum_required(VERSION 3.5.1)
project(realtime)
add_executable(realtime realtime.cpp)
target_link_libraries(realtime pthread)

SET(CMAKE_CXX_FLAGS "--std=c++14") 
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

