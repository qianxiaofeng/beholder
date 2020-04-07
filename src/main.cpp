#include <iostream>

struct U128 {
  uint64_t lo, hi;

  template<typename Archive>
  void archive(Archive &ar) {
    ar(lo, hi);
  }
};

struct U256 {
  uint64_t ll, lh, hl, hh;

  template<typename Archive>
  void archive(Archive &ar) {
    ar(ll, lh, hl, hh);
  }
};

struct Archive {

  explicit Archive(std::ostream &os) : os{os} {

  }

  void hello(const std::string &a) {
    os << a << std::endl;
  }

  template<typename ... Args>
  void operator()(Args ... args) {
    serialize(args...);
  }

  template<typename Head, typename ... Tail>
  void serialize(Head head, Tail ... tail) {
    serialize(head);
    serialize(tail...);
  }

  template<typename T>
  void serialize(T t) {
    hello("primary template");
  }

  template<>
  void serialize<uint64_t>(uint64_t t) {
    hello(std::to_string(t));
  }

  template<typename Integer, std::enable_if_t<std::is_integral<Integer>::value, int> = 0>
  void f(Integer i) {
    std::cout << "use integer" << std::endl;
  }

  template<typename Float, std::enable_if_t<std::is_floating_point<Float>::value, int> = 0>
  void f(Float f) {
    std::cout << "use float" << std::endl;

  }
 private:
  std::ostream &os;
};

int main() {
//  std::cout << "Hello, World!" << std::endl;
  U128 x{1, 2};
  U256 y{4, 3, 2, 1};

  Archive a(std::cout);
//  a.hello("hello");
//  a.serialize(x.hi, x.lo);
  x.archive(a);
  y.archive(a);
  return 0;
}
