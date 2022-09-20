#include <iostream>

class TestStatic {
  static int i;

public:
  TestStatic() = default;
  ~TestStatic() = default;
  static void setI(int val) { i = val; }
  static int getI() { return i; }
};

int TestStatic::i = 99;

int main(int argc, char const *argv[]) {
  std::cout << "i = " << TestStatic::getI() << "\n";
  TestStatic::setI(100);
  std::cout << "i = " << TestStatic::getI() << "\n";
  return 0;
}
