#include <iostream>
#include <ostream>
#include <random>

class TestRandom {
  std::uniform_int_distribution<int> d;
  std::default_random_engine e;

public:
  static int i;
  TestRandom() { d = std::uniform_int_distribution<int>(0, 99); }

  ~TestRandom() = default;

  void Test() {
    for (int i = 0; i < 10; i++) {
      std::cout << d(e) << " ";
    }
    std::cout << std::endl;
  }
};

int main(int argc, char const *argv[]) {
  TestRandom r1;
  r1.Test();
  // r1.Test();
  // r1.Test();
  TestRandom r2;
  r2.Test();
  return 0;
}
