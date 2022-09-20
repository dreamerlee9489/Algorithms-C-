#include <iostream>
#include <random>

class TestRandom {
  std::default_random_engine e1;
  std::uniform_int_distribution<int> d1;
  static std::default_random_engine e2;
  static std::uniform_int_distribution<int> d2;

public:
  TestRandom() { d1 = std::uniform_int_distribution<int>(0, 99); }

  ~TestRandom() = default;

  void Test() {
    std::cout << "d1: ";
    for (int i = 0; i < 10; i++) {
      std::cout << d1(e1) << " ";
    }
    std::cout << std::endl;
  }

  static void TestStatic() {
    std::cout << "d2: ";
    for (int i = 0; i < 10; i++) {
      std::cout << d2(e2) << " ";
    }
    std::cout << std::endl;
  }
};

std::uniform_int_distribution<int> TestRandom::d2 =
    std::uniform_int_distribution<int>(-99, 0);
std::default_random_engine TestRandom::e2 = std::default_random_engine();

int main(int argc, char const *argv[]) {
  TestRandom r1;
  r1.Test();
  r1.Test();
  std::cout << "--------------------------\n";
  TestRandom r2;
  r2.Test();
  r2.Test();
  std::cout << "--------------------------\n";
  TestRandom::TestStatic();
  TestRandom::TestStatic();
  return 0;
}
