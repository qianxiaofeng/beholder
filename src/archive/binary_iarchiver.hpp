//
// Created by Xiaofeng Qian on 12/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_BINARY_IARCHIVER_HPP_
#define BEHOLDER_SRC_ARCHIVE_BINARY_IARCHIVER_HPP_

#include "iarchiver.hpp"
#include <iostream>

namespace beholder::archive {
class BinaryIArchiver : public IArchiver<BinaryIArchiver> {
 public:
  explicit BinaryIArchiver(std::istream &is) :
      its_is(is),
      IArchiver<BinaryIArchiver>(this) {}
  void load_binary(void *const data, std::streamsize size) {
    auto const read_size = its_is.rdbuf()->sgetn(reinterpret_cast<char *>( data), size);
    assert(size==read_size);
  }
 private:
  std::istream &its_is;
};

template<typename T>
typename std::enable_if_t<std::is_arithmetic_v<T>, void>
load_impl(BinaryIArchiver &ar, T &t) {
  ar.load_binary(std::addressof(t), sizeof(t));
}

//template <typename T>
//typename std::enable_if_t<std::is_class_v<T>,void>
//load_impl(BinaryIArchiver &ar, T &t){
//
//}

}

#endif //BEHOLDER_SRC_ARCHIVE_BINARY_IARCHIVER_HPP_
