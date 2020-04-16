cmake_minimum_required(VERSION 3.5.1)
project(pinthreads)
add_executable(pinthreads pinthreads.cpp)
target_link_libraries(pinthreads pthread)

SET(CMAKE_CXX_FLAGS "--std=c++14") 
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabi-g++)

