//
// Created by Xiaofeng Qian on 10/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_TYPE_BINARY_DATA_HPP_
#define BEHOLDER_SRC_ARCHIVE_TYPE_BINARY_DATA_HPP_
#include "../trait/is_binary_data.hpp"
namespace beholder::archive::type {
using beholder::archive::trait::IsBinaryDataV;

template<typename InputArchiver, typename T>
typename std::enable_if_t<IsBinaryDataV<T>, void>
load_binary(InputArchiver &ar, T &t) {
  ar.load_binary(std::addressof(t), sizeof(t));
}
}
#endif //BEHOLDER_SRC_ARCHIVE_TYPE_BINARY_DATA_HPP_
