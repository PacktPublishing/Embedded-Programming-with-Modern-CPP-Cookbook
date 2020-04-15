cmake_minimum_required(VERSION 3.5.1)
project(shmatomic)
add_executable(shmatomic shmatomic.cpp)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

SET(CMAKE_CXX_FLAGS "--std=c++11")
target_link_libraries(shmatomic pthread rt)

set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)

