//
// Created by Xiaofeng Qian on 30/3/20.
//

#include "block_log_reader.hpp"
#include <iostream>
namespace beholder {
void BlockLogReader::open(std::string const &path) {
  file.open(path, std::ios::in | std::ios::binary);
  if (file.is_open()) {
    std::cout << "open success" << std::endl;
  } else {
    std::cout << "open failed" << std::endl;
  }
  iar = std::make_unique<archive::BinaryIArchiver>(file);
}
void BlockLogReader::read_all(BlockLog &blog) {
  iar->load(blog.version);
  iar->load(blog.first_block_num);
  read_tail_uint64(blog.pos);
  file.seekg(blog.pos);
  iar->load(blog.block_.header);
}

void BlockLogReader::read_tail_uint64(uint64_t &to) {
  auto old_pos = file.tellg();
  file.seekg(-sizeof(uint64_t), std::ios::end);
  iar->load(to);
  file.seekg(old_pos);
}
}