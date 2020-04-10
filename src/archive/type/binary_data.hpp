//
// Created by Xiaofeng Qian on 10/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_TYPE_BINARY_DATA_HPP_
#define BEHOLDER_SRC_ARCHIVE_TYPE_BINARY_DATA_HPP_
#include "../input_archiver.hpp"

namespace beholder::archive::type {
template<typename InputArchiver, typename T>
typename std::enable_if_t<std::is_arithmetic_v<T>, void>
load_binary(InputArchiver &ar, T &t) {
  ar.load_binary(std::addressof(t), sizeof(t));
}

}
#endif //BEHOLDER_SRC_ARCHIVE_TYPE_BINARY_DATA_HPP_
