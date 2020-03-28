cmake_minimum_required(VERSION 3.5.1)
project(ipc4)
add_executable(ipc4 ipc4.cpp)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

SET(CMAKE_CXX_FLAGS "--std=c++11")
target_link_libraries(ipc4 rt)

set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)

