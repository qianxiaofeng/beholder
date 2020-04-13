//
// Created by Xiaofeng Qian on 13/4/20.
//

#ifndef BEHOLDER_SRC_TYPE_NAME_HPP_
#define BEHOLDER_SRC_TYPE_NAME_HPP_
#include <cstdint>
#include <string>

struct Name {
  uint64_t value;

 public:
  static Name from_string(std::string_view str) {
    uint64_t n = 0;
    int i = 0;
    for (; str[i] && i < 12; ++i) {
      // NOTE: char_to_symbol() returns char type, and without this explicit
      // expansion to uint64 type, the compilation fails at the point of usage
      // of string_to_name(), where the usage requires constant (compile time) expression.
      n |= (char_to_symbol(str[i]) & 0x1fu) << (64u - 5u*(i + 1u));
    }

    // The for-loop encoded up to 60 high bits into uint64 'name' variable,
    // if (strlen(str) > 12) then encode str[12] into the low (remaining)
    // 4 bits of 'name'
    if (i==12)
      n |= char_to_symbol(str[12]) & 0x0Fu;
    return Name{n};
  }

  [[nodiscard]] std::string to_string() const {
    char buffer[13];
    auto end = write_as_string(buffer, buffer + sizeof(buffer));
    return {buffer, end};
  }

  template<typename Archiver>
  void serialize(Archiver &ar) {
    ar(value);
  }

 private:
  static constexpr uint64_t char_to_symbol(const char &c) {
    if (c >= 'a' && c <= 'z')
      return (c - 'a') + 6;
    if (c >= '1' && c <= '5')
      return (c - '1') + 1;
    return 0;
  }

  char *write_as_string(char *begin, const char *end, bool dry_run = false) const {
    static const char *charmap = ".12345abcdefghijklmnopqrstuvwxyz";
    constexpr uint64_t mask = 0xF800000000000000ull;

    if (dry_run || (begin + 13 < begin) || (begin + 13 > end)) {
      char *actual_end = begin + length();
      if (dry_run || (actual_end < begin) || (actual_end > end)) return actual_end;
    }

    auto v = value;
    for (auto i = 0; i < 13; ++i, v <<= 5u) {
      if (v==0) return begin;

      auto indx = (v & mask) >> (i==12u ? 60u : 59u);
      *begin = charmap[indx];
      ++begin;
    }

    return begin;
  }

  [[nodiscard]] uint8_t length() const {
    constexpr uint64_t mask = 0xF800000000000000ull;

    if (value==0)
      return 0;

    uint8_t l = 0;
    uint8_t i = 0;
    for (auto v = value; i < 13; ++i, v <<= 5u) {
      if ((v & mask) > 0) {
        l = i;
      }
    }

    return l + 1;
  }

};

#endif //BEHOLDER_SRC_TYPE_NAME_HPP_
