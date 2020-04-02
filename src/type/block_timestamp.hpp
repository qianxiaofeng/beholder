//
// Created by Xiaofeng Qian on 30/3/20.
//

#ifndef BEHOLDER_SRC_TYPE_BLOCK_TIMESTAMP_HPP_
#define BEHOLDER_SRC_TYPE_BLOCK_TIMESTAMP_HPP_
#include <cstdint>
#include <ostream>

struct BlockTimestamp {
  uint32_t slot;
  friend std::ostream &operator<<(std::ostream &os, const BlockTimestamp &timestamp);
};

#endif //BEHOLDER_SRC_TYPE_BLOCK_TIMESTAMP_HPP_
