cmake_minimum_required(VERSION 3.15)
project(beholder)

set(CMAKE_CXX_STANDARD 20)

add_executable(beholder src/main.cpp src/reader.cpp src/reader.hpp src/block_log.cpp src/block_log.hpp src/block_log_reader.cpp src/block_log_reader.hpp src/type/signed_block.cpp src/type/signed_block.hpp src/type/signed_block_header.cpp src/type/signed_block_header.hpp src/type/block_header.cpp src/type/block_header.hpp src/type/block_timestamp.cpp src/type/block_timestamp.hpp)

add_subdirectory(external)
add_subdirectory(test)