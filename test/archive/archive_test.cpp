//
// Created by Xiaofeng Qian on 7/4/20.
//

#include <gtest/gtest.h>
#include "../../src/archive/archive.hpp"
#include "../../src/archive/binary_output_archive.hpp"

struct MyData {
  uint64_t a, b, c, d;

  template<typename Archive>
  void archive(Archive &ar) {
    ar(a, b, c, d);
  }
};

TEST(archive, hello) { //NOLINT
  MyData d1{1, 2, 3, 4};
  MyData d2{10, 20, 30, 40};
  BinaryOutputArchive a{std::cout};
  a(d1, d2);
}