cmake_minimum_required(VERSION 3.5.1)
project(pwm)
add_executable(pwm pwm.cpp)
target_link_libraries(pwm wiringPi)

