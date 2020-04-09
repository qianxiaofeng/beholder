//
// Created by Xiaofeng Qian on 8/4/20.
//

#ifndef BEHOLDER_SRC_ARCHIVE_ARCHIVER_HPP_
#define BEHOLDER_SRC_ARCHIVE_ARCHIVER_HPP_
#include <cstdint>
#include <iostream>
#include <iomanip>

class Archiver {
 public:
  explicit Archiver(std::ostream &os) : its_os(os) {}

  template<typename ... Args>
  void operator()(Args ... args) {
    saveImpl(args ...);
  }

  template<typename T>
  void save(T user_data) {
    ArchiveContainer<T, ArchiveBaseConcept, ArchiveModel> container(user_data);
    container.save(*this);
  }

 private:
  std::ostream &its_os;

  template<typename Head, typename ... Tail>
  void saveImpl(Head head, Tail ... tail) {
    saveImpl(head);
    saveImpl(tail ...);
  }

  template<typename Head>
  void saveImpl(Head head) {
    save(head);
  }

  class ArchiveBaseConcept {
   public:
    virtual void save(Archiver &ar) = 0;
  };

  template<typename T>
  class ArchiveHolder {
   public:
    explicit ArchiveHolder(T &data) : data_(&data) {}
    T &get() { return *data_; }
   private:
    T *data_;
  };

  template<typename ArchiveHolder>
  class ArchiveModel : public ArchiveHolder, public ArchiveBaseConcept {
   public:
    using ArchiveHolder::ArchiveHolder;

    void save(Archiver &ar) override {
      serialize(this->ArchiveHolder::get(), ar);
    }

    template<typename T>
    typename std::enable_if_t<std::is_class_v<T>, T>
    serialize(T &data, Archiver &ar) {
      this->ArchiveHolder::get().member_visit(ar);
    }

    template<typename T>
    typename std::enable_if_t<std::is_arithmetic_v<T>, T>
    serialize(T &data, Archiver &ar) {
      ar.its_os << data;
    }
  };

  template<typename T, class ArchiveBaseConcept, template<class> class ArchiveModel>
  class ArchiveContainer {
   public:
    explicit ArchiveContainer(T &obj) : self_(new ArchiveModel<ArchiveHolder<T>>(obj)) {}

    void save(Archiver &ar) {
      self_->save(ar);
    }
   private:
    ArchiveBaseConcept *const self_;
  };
};

#endif //BEHOLDER_SRC_ARCHIVE_ARCHIVER_HPP_
