//
// Created by Xiaofeng Qian on 30/3/20.
//

#include "block_log_reader.hpp"
#include <iostream>
namespace beholder {
void BlockLogReader::open(std::string path) {
  file.open(path, std::ios::in | std::ios::binary);
  if (file.is_open()) {
    std::cout << "open success" << std::endl;
  } else {
    std::cout << "open failed" << std::endl;
  }
}
void BlockLogReader::read_all(BlockLog &blog) {
  read_uint32(blog.version);
  read_uint32(blog.first_block_num);
  read_tail_uint64(blog.pos);
  file.seekg(blog.pos);
  read_uint32(blog.header_timestamp.slot);//expect 1163721896, expect pos 587274
}
void BlockLogReader::read_uint32(uint32_t &to) {
    file.read((char *)&to, sizeof(uint32_t));
}
void BlockLogReader::read_tail_uint64(uint64_t &to) {
  auto old_pos = file.tellg();
  file.seekg(-sizeof(uint64_t),std::ios::end);
  file.read((char *)&to, sizeof(uint64_t));
  file.seekg(old_pos);
}
}