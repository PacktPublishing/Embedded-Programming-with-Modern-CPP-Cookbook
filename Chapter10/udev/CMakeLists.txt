cmake_minimum_required(VERSION 3.5.1)
project(udev)
add_executable(usb udev.cpp)
target_link_libraries(usb udev)

