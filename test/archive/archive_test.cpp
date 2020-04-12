//
// Created by Xiaofeng Qian on 7/4/20.
//

#include <gtest/gtest.h>
#include <tuple>
#include "../../src/archive/archiver.hpp"
#include "../../src/archive/input_archiver.hpp"
#include "../../src/archive/binary_iarchiver.hpp"
#include "../../src/archive/iarchiver.hpp"

struct MyDataA {
  uint64_t a, b, c, d;

  void member_visit(Archiver &ar) {
    ar(a, b, c, d);
  }
};

TEST(archive, hello) { //NOLINT
  MyDataA da1{1, 2, 3, 4};
  MyDataA da2{10, 20, 30, 40};

  Archiver aaa{std::cout};
  aaa.save(da1);
  aaa.save(da1);
  aaa.save(10);
  aaa.save(da2);
  aaa.save(uint64_t(123));
}

struct MyDataB {
  uint64_t x, y, z;

  auto reflect() {
    return std::vector{
        std::make_pair("x", x),
        std::make_pair("y", y),
        std::make_pair("z", z)
    };
  }
};

struct membuf : std::streambuf {
  membuf(char *begin, char *end) {
    this->setg(begin, begin, end);
  }
};

TEST(archive, input_archive_int) { //NOLINT
  using beholder::archive::InputArchiver;
  int a, b, c, d;
  a = b = c = d = 100;

  unsigned char buffer[] = {0x01, 0x00, 0x00, 0x00,
                            0x02, 0x00, 0x00, 0x00,
                            0x03, 0x00, 0x00, 0x00,
                            0x04, 0x00, 0x00, 0x00,
                            '\0'
  };

  membuf sbuf((char *) buffer, (char *) buffer + sizeof(buffer) - 1);
  std::istream in(&sbuf);

  InputArchiver iar(in);
  iar.load(a);
  iar.load(b);
  iar.load(c);
  iar.load(d);

  EXPECT_EQ(a, 1);
  EXPECT_EQ(b, 2);
  EXPECT_EQ(c, 3);
  EXPECT_EQ(d, 4);
}

TEST(archive, input_archive_struct) { //NOLINT
  using beholder::archive::InputArchiver;
  MyDataB d{};
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

  InputArchiver iar(in);
  iar.load(d);

  EXPECT_EQ(d.x, 1);
  EXPECT_EQ(d.y, 2);
  EXPECT_EQ(d.z, 3);
}

struct MyDataD {
  uint64_t x, y, z;

  template<typename Archiver>
  void serialize(Archiver &ar) {
    ar(x, y, z);
  }
};

TEST(iarchive, simple) {//NOLINT
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

  MyDataD d{};
  iar.load(d);

  EXPECT_EQ(d.x, 1);
  EXPECT_EQ(d.y, 2);
  EXPECT_EQ(d.z, 3);
}