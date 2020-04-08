cmake_minimum_required(VERSION 3.15)
project(beholder)

set(CMAKE_CXX_STANDARD 20)

add_executable(beholder src/main.cpp src/archive/archive.cpp src/archive/archive.hpp src/archive/binary_output_archive.cpp src/archive/binary_output_archive.hpp)

add_subdirectory(external)
add_subdirectory(test)