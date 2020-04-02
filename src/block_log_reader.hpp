//
// Created by Xiaofeng Qian on 30/3/20.
//

#ifndef BEHOLDER_BLOCK_LOG_READER_HPP
#define BEHOLDER_BLOCK_LOG_READER_HPP
#include "block_log_reader.hpp"
#include "block_log.hpp"
#include <fstream>
#include <string>
namespace beholder {
class BlockLogReader {
 public:
  void open(std::string path);
  void read_all(BlockLog &blog);
  void read_uint32(uint32_t& to);
  void read_tail_uint64(uint64_t& pos);
 private:
  std::ifstream file;
};
}
#endif // BEHOLDER_BLOCK_LOG_READER_HPP
