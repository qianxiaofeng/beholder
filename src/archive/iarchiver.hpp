//
// Created by Xiaofeng Qian on 12/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_IARCHIVER_HPP_
#define BEHOLDER_SRC_ARCHIVE_IARCHIVER_HPP_

#include <type_traits>

namespace beholder::archive {

template<typename ArchiverType>
class IArchiver {
 public:
  explicit IArchiver(ArchiverType *const derived) : self(derived) {}

  template<typename ... Args>
  ArchiverType &operator()(Args &&... args) {
    process(std::forward<Args>(args)...);
    return *self;
  }

  template<typename T>
  ArchiverType &load(T &&t) {
    process_impl(std::forward<T>(t));
    return *self;
  }
 private:
  ArchiverType *const self;

  template<typename Head, typename ... Tail>
  void process(Head &&head, Tail &&... tail) {
    process(std::forward<Head>(head));
    process(std::forward<Tail>(tail) ...);
  }

  template<typename Head>
  void process(Head &&head) {
    process_impl(std::forward<Head>(head));
  }

  template<typename T>
//  ArchiverType &
  typename std::enable_if_t<std::is_arithmetic_v<
      std::remove_reference_t<T>
  >, void>
  process_impl(T &&t) {
    load_impl(*self, std::forward<T>(t));
//    return *self;
  }

  template<typename T>
  typename std::enable_if_t<std::is_class_v<
      std::remove_reference_t<T>
  >, void>
  process_impl(T &&t) {
    t.serialize(*self);
  }
};
}
#endif //BEHOLDER_SRC_ARCHIVE_IARCHIVER_HPP_
