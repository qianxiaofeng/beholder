//
// Created by Xiaofeng Qian on 30/3/20.
//

#include "block_timestamp.hpp"
std::ostream &operator<<(std::ostream &os, const BlockTimestamp &timestamp) {
  os << "slot: " << timestamp.slot;
  return os;
}
