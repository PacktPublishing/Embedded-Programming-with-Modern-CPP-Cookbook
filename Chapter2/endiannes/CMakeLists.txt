cmake_minimum_required(VERSION 3.5.1)
project(endianness)
add_executable(endianness endianness.cpp)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

SET(CMAKE_CXX_FLAGS "--std=c++11")
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
