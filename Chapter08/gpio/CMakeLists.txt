cmake_minimum_required(VERSION 3.5.1)
project(gpio)
add_executable(gpio gpio.cpp)
target_link_libraries(gpio wiringPi)

