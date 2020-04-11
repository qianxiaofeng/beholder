//
// Created by Xiaofeng Qian on 10/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_TRAIT_IS_BINARY_DATA_HPP_
#define BEHOLDER_SRC_ARCHIVE_TRAIT_IS_BINARY_DATA_HPP_
#include <type_traits>
namespace beholder::archive::trait {

template<typename T, typename _ = void>
class IsBinaryData : public std::false_type {};

template<typename T>
class IsBinaryData<T, std::enable_if_t<std::is_arithmetic_v<T>>> : public std::true_type {};

template<class T>
inline constexpr bool IsBinaryDataV = IsBinaryData<T>::value;

}

#endif //BEHOLDER_SRC_ARCHIVE_TRAIT_IS_BINARY_DATA_HPP_
