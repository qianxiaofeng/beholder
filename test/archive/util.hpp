//
// Created by Xiaofeng Qian on 13/4/20.
//

#ifndef BEHOLDER_TEST_ARCHIVE_UTIL_HPP_
#define BEHOLDER_TEST_ARCHIVE_UTIL_HPP_
#include <iostream>

struct membuf : std::streambuf {
  membuf(char *begin, char *end) {
    this->setg(begin, begin, end);
  }
};

struct MyDataA {
  uint64_t x, y, z;

  template<typename Archiver>
  void serialize(Archiver &ar) {
    ar(x, y, z);
  }

  friend bool operator==(const MyDataA &lhs, const MyDataA &rhs) {
    return lhs.x==rhs.x &&
        lhs.y==rhs.y &&
        lhs.z==rhs.z;
  }
};

struct MyDataB {
  MyDataA a;
  int size;

  template<typename Archiver>
  void serialize(Archiver &ar) {
    ar(a, size);
  }
  friend bool operator==(const MyDataB &lhs, const MyDataB &rhs) {
    return lhs.a==rhs.a &&
        lhs.size==rhs.size;
  }
};
#endif //BEHOLDER_TEST_ARCHIVE_UTIL_HPP_
