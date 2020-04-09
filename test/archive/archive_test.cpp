//
// Created by Xiaofeng Qian on 7/4/20.
//

#include <gtest/gtest.h>
#include "../../src/archive/archiver.hpp"

struct MyDataA {
  uint64_t a, b, c, d;

  void member_visit(Archiver &ar) {
    ar(a, b, c, d);
  }
};

struct MyDataB {
  uint64_t x, y, z;
};

void member_visit(MyDataB &b, Archiver &ar) {
  ar(b.x, b.y, b.z);
}

TEST(archive, hello) { //NOLINT
  MyDataA da1{1, 2, 3, 4};
  MyDataA da2{10, 20, 30, 40};
//  BinaryOutputArchive a{std::cout};
//  a(d1, d2);

  Archiver aaa{std::cout};
  aaa.save(da1);
  aaa.save(da1);
  aaa.save(10);
  aaa.save(da2);
  aaa.save(uint64_t(123));

}