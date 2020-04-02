//
// Created by Xiaofeng Qian on 30/3/20.
//

#ifndef BEHOLDER_BLOCK_LOG_HPP
#define BEHOLDER_BLOCK_LOG_HPP
#include <cstdint>
#include <ostream>
#include "type/signed_block.hpp"
#include "type/block_timestamp.hpp"
namespace beholder {
struct BlockLog {
  uint32_t version;
  uint32_t first_block_num;
  uint64_t pos; //at end of file
  friend std::ostream &operator<<(std::ostream &os, const BlockLog &log);

  SignedBlock header;
  BlockTimestamp header_timestamp;
  };
} // namespace beholder

#endif // BEHOLDER_BLOCK_LOG_HPP
