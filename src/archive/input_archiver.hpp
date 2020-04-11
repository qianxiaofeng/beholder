//
// Created by Xiaofeng Qian on 9/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_INPUT_ARCHIVER_HPP_
#define BEHOLDER_SRC_ARCHIVE_INPUT_ARCHIVER_HPP_
#include <iostream>
#include "type/binary_data.hpp"
#include "trait/is_binary_data.hpp"

namespace beholder::archive {
using beholder::archive::trait::IsBinaryDataV;

class InputArchiver {
 public:
  explicit InputArchiver(std::istream &is) : its_is(is) {}

  template<typename T>
  void load(T &t) {
    IArchiveContainer<T> container(t);
    container.load(*this);
  }

  void load_binary(void *const data, std::streamsize size) {
    auto const readSize = its_is.rdbuf()->sgetn(reinterpret_cast<char *>( data ), size);
    assert(size==readSize);//TODO maybe throw exception
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

  class IArchiveModel {
   public:
    explicit IArchiveModel() = default;

    template<typename T>
    typename std::enable_if_t<IsBinaryDataV<T>, void>
    load(InputArchiver &iar, IArchiveHolder<T> &holder) {
      beholder::archive::type::load_binary<InputArchiver, T>(iar, holder.get());
    }

    template<typename T>
    typename std::enable_if_t<std::is_class_v<T>, void>
    load(InputArchiver &iar, IArchiveHolder<T> &t) {
      std::vector members = t.get().reflect();
      for (auto itr = members.begin(); itr!=members.end(); ++itr) {
        iar.load(itr->second);
      }
      printf("\n");
    }
  };

  template<typename T>
  class IArchiveContainer : public IArchiveConcept {
   public:

    explicit IArchiveContainer(T &t) : model_(new IArchiveModel()), holder_(new IArchiveHolder<T>(t)) {}

    void load(InputArchiver &iar) override {
//      beholder::archive::type::load_binary<InputArchiver, T>(iar, holder_.get());
      model_->load(iar, *holder_);
    }

   private:
    IArchiveModel *model_;
    IArchiveHolder<T> *holder_;
  };

};
}

#endif //BEHOLDER_SRC_ARCHIVE_INPUT_ARCHIVER_HPP_
