cmake_minimum_required(VERSION 3.5.1)
project(gpiod)
add_executable(gpiod gpiod.cpp)
target_link_libraries(gpiod gpiodcxx)

