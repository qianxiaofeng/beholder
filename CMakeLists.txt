cmake_minimum_required(VERSION 3.15)
project(beholder)

set(CMAKE_CXX_STANDARD 20)

add_executable(beholder src/main.cpp src/archive/archiver.cpp src/archive/archiver.hpp src/archive/input_archiver.cpp src/archive/input_archiver.hpp src/archive/type/vector.cpp src/archive/type/vector.hpp src/archive/type/binary_data.cpp src/archive/type/binary_data.hpp src/archive/trait/is_binary_data.cpp src/archive/trait/is_binary_data.hpp src/archive/iarchiver.cpp src/archive/iarchiver.hpp src/archive/binary_iarchiver.cpp src/archive/binary_iarchiver.hpp)

add_subdirectory(external)
add_subdirectory(test)