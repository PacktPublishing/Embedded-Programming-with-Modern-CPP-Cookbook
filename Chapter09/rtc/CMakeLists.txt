cmake_minimum_required(VERSION 3.5.1)
project(rtc)
add_executable(rtc rtc.cpp)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)
