//
// Created by Xiaofeng Qian on 30/3/20.
//

#include "block_log.hpp"

std::ostream &beholder::operator<<(std::ostream &os, const beholder::BlockLog &log) {
  os << "version: " << log.version << " first_block_num: " << log.first_block_num << " pos: " << log.pos  << " header_timestamp: " << log.header_timestamp;
  return os;
}
