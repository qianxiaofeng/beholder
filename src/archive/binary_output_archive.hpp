//
// Created by Xiaofeng Qian on 7/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_BINARY_OUTPUT_ARCHIVE_HPP_
#define BEHOLDER_SRC_ARCHIVE_BINARY_OUTPUT_ARCHIVE_HPP_
#include "archive.hpp"
#include <iostream>
#include <iomanip>
#include <string>

class BinaryOutputArchive : public Archive<BinaryOutputArchive> {
 public:
  explicit BinaryOutputArchive(std::ostream &os) :
      Archive<BinaryOutputArchive>(this),
      its_os(os) {}
  void save(uint64_t a) {
    its_os << std::hex << std::setfill('0') << std::setw(2) << a;
  }
 private:
  std::ostream &its_os;
};

#endif //BEHOLDER_SRC_ARCHIVE_BINARY_OUTPUT_ARCHIVE_HPP_
