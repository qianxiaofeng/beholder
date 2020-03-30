cmake_minimum_required(VERSION 3.15)
project(beholder)

set(CMAKE_CXX_STANDARD 20)

add_executable(beholder src/main.cpp)

add_subdirectory(external)
add_subdirectory(test)