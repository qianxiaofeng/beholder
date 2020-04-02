//
// Created by Xiaofeng Qian on 30/3/20.
//
#include "block_log.hpp"
#include "block_log_reader.hpp"
#include <iostream>

namespace beholder {
void read() {
  auto block_index_path = "/Users/deadlock/eos/data/blocks/blocks.index";
  auto block_log_path = "/Users/deadlock/eos/data/blocks/blocks.log";

  BlockLog blog{};
  BlockLogReader blog_reader;

  blog_reader.open(block_log_path);
  blog_reader.read_all(blog);

  std::cout<< blog << std::endl;
}
} // namespace beholder