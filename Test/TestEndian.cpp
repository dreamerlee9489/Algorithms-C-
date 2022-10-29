#include <ios>
#include <iostream>

union Test {
  char chs[4];
  int i;
};

uint32_t ByteSwap4(uint32_t data) {
  return (data >> 24) & 0x000000ff | (data >> 8) & 0x0000ff00 |
         (data << 8) & 0x00ff0000 | (data << 24) & 0xff000000;
}

int main(int argc, char const *argv[]) {
  Test t;
  t.chs[0] = 0x12;
  t.chs[1] = 0x34;
  t.chs[2] = 0x56;
  t.chs[3] = 0x78;

  std::cout << std::showbase;
  std::cout << (uintptr_t)&t.chs[0] << " " << (uintptr_t)&t.chs[1] << "\n";
  std::cout << std::hex << t.i << "\n";
  std::cout << ByteSwap4(t.i) << "\n";
  std::cout << std::noshowbase;
  return 0;
}
