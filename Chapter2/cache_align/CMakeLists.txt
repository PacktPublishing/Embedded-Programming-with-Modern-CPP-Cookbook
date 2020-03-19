cmake_minimum_required(VERSION 3.5.1)
project(cache_align)
add_executable(cache_align cache_align.cpp)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

SET(CMAKE_CXX_FLAGSE "--std=c++11")
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
