#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<int> vec = {1, 2, 3, 4, 5};
  int arr[5] = {6, 7, 8, 9, 10};
  int i = 100;
  bool b = true;

  std::cout << std::showbase;
  std::cout << std::oct << (uintptr_t)&vec[4] << " " << (uintptr_t)&arr[4]
            << " " << (uintptr_t)&i << "\n";
  std::cout << std::dec << (uintptr_t)&vec[4] << " " << (uintptr_t)&arr[4]
            << " " << (uintptr_t)&i << "\n";
  std::cout << std::hex << (uintptr_t)&vec[4] << " " << (uintptr_t)&arr[4]
            << " " << (uintptr_t)&i << "\n";
  std::cout << std::noshowbase;

  std::cout << std::boolalpha << b << " " << std::noboolalpha << false << "\n";
  std::cout << std::setprecision(3) << std::sqrt(2) << " "
            << std::setprecision(6) << std::sqrt(2) << "\n";

  std::cout << sizeof(long) << " " << sizeof(long long) << " " << sizeof(void *)
            << "\n";
  return 0;
}
