//
// Created by Xiaofeng Qian on 9/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_INPUT_ARCHIVER_HPP_
#define BEHOLDER_SRC_ARCHIVE_INPUT_ARCHIVER_HPP_
#include <iostream>
#include "type/binary_data.hpp"

class InputArchiver {
 public:
  explicit InputArchiver(std::istream &is) : its_is(is) {}

  template<typename T>
  int load(T &t) {
    int old_pos = its_is.tellg();
    IArchiveContainer<T, IArchiveHolder> container(t);
    container.load(*this);
    int new_pos = its_is.tellg();
    return new_pos - old_pos;
  }

  void load_binary(void *const data, std::streamsize size) {
    auto const readSize = its_is.rdbuf()->sgetn(reinterpret_cast<char *>( data ), size);
    assert(size==readSize);
  }

 private:
  std::istream &its_is;

  class IArchiveConcept {
   public:
    virtual void load(InputArchiver &iar) = 0;
  };

  template<typename T>
  class IArchiveHolder {
   public:
    explicit IArchiveHolder(T &data) : data_(&data) {}

    T &get() {
      return *data_;
    }

   private:
    T *data_;
  };

  template<typename T, template<class> class IArchiveHolder>
  class IArchiveContainer : public IArchiveConcept {
   public:
//    using IArchiveHolder<T>::IArchiveHolder;

    explicit IArchiveContainer(T &t) : holder_(IArchiveHolder(t)) {}
    void load(InputArchiver &iar) override {
      beholder::archive::type::load_binary<InputArchiver, T>(iar, holder_.get());
    }
   private:
    IArchiveHolder<T> holder_;
  };

};

#endif //BEHOLDER_SRC_ARCHIVE_INPUT_ARCHIVER_HPP_
