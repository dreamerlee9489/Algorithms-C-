#include <iostream>

int main(int argc, char const *argv[]) {
  int arr[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  std::cout << std::dec << (size_t)arr << " " << (size_t)&arr[0][0] << "\n";
  std::cout << sizeof(arr) << "\n";
  return 0;
}
