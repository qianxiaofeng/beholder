//
// Created by Xiaofeng Qian on 30/3/20.
//

#ifndef BEHOLDER_BLOCK_LOG_READER_HPP
#define BEHOLDER_BLOCK_LOG_READER_HPP
#include "block_log_reader.hpp"
#include "block_log.hpp"
#include <fstream>
#include <string>
#include "archive/binary_iarchiver.hpp"
namespace beholder {
class BlockLogReader {
 public:
  void open(std::string const &path);
  void read_all(BlockLog &blog);
 private:
  std::ifstream file;
  std::unique_ptr<archive::BinaryIArchiver> iar;

  void read_tail_uint64(uint64_t &pos);
};
}
#endif // BEHOLDER_BLOCK_LOG_READER_HPP
