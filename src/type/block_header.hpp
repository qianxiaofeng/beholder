//
// Created by Xiaofeng Qian on 30/3/20.
//

#ifndef BEHOLDER_SRC_TYPE_BLOCK_HEADER_HPP_
#define BEHOLDER_SRC_TYPE_BLOCK_HEADER_HPP_

#include "block_timestamp.hpp"
#include "name.hpp"
struct BlockHeader {
  BlockTimestamp timestamp;
  Name producer;
  uint16_t confirmed;

  template<typename Archiver>
  void serialize(Archiver &ar) {
    ar(timestamp, producer, confirmed);
  }
};

#endif //BEHOLDER_SRC_TYPE_BLOCK_HEADER_HPP_
