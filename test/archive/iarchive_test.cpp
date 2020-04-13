//
// Created by Xiaofeng Qian on 7/4/20.
//

#include <gtest/gtest.h>
#include "../../src/archive/binary_iarchiver.hpp"
#include "../../src/archive/iarchiver.hpp"
#include "util.hpp"

TEST(iarchive, load_int) {//NOLINT
  using beholder::archive::BinaryIArchiver;

  unsigned char buffer[] = {0x01, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x02, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x03, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            '\0'
  };
  membuf sbuf((char *) buffer, (char *) buffer + sizeof(buffer) - 1);
  std::istream in(&sbuf);
  BinaryIArchiver iar{in};

  int a = 100;
  iar.load(a);

  EXPECT_EQ(a, 1);
}

TEST(iarchive, load_struct) {//NOLINT
  using beholder::archive::BinaryIArchiver;

  unsigned char buffer[] = {0x01, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x02, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x03, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            '\0'
  };
  membuf sbuf((char *) buffer, (char *) buffer + sizeof(buffer) - 1);
  std::istream in(&sbuf);
  BinaryIArchiver iar{in};

  MyDataA a{};
  iar.load(a);

  MyDataA expected{1, 2, 3};

  EXPECT_EQ(a, expected);
}

TEST(iarchive, load_nest_struct) {//NOLINT
  using beholder::archive::BinaryIArchiver;

  unsigned char buffer[] = {0x01, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x02, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x03, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            0x0a, 0x00, 0x00, 0x00,
                            0x00, 0x00, 0x00, 0x00,
                            '\0'
  };
  membuf sbuf((char *) buffer, (char *) buffer + sizeof(buffer) - 1);
  std::istream in(&sbuf);
  BinaryIArchiver iar{in};

  MyDataB b{};
  iar.load(b);

  MyDataA expected_a{1, 2, 3};
  MyDataB expected_b{expected_a, 10};

  EXPECT_EQ(b, expected_b);
}