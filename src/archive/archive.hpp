//
// Created by Xiaofeng Qian on 7/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_ARCHIVE_HPP_
#define BEHOLDER_SRC_ARCHIVE_ARCHIVE_HPP_
#include <cstdint>

template<typename Derived>
class Archive {
 public:
  explicit Archive(Derived *const derived) : self{derived} {}

  template<typename ... Args>
  void operator()(Args ... args) {
    process(args...);
  }
 private:
  Derived *const self;

  template<typename Head, typename ... Tail>
  void process(Head head, Tail ... tail) {
    process(head);
    process(tail ...);
  }

  template<typename Head>
  void process(Head head) {
    head.archive(*self);
  }

  template <>
  void process<uint64_t>(uint64_t head){
    self->save(head);
  }
};

#endif //BEHOLDER_SRC_ARCHIVE_ARCHIVE_HPP_
