#include <iostream>
#include <iterator>
#include <list>
#include <vector>

int main(int argc, char const *argv[]) {
  std::list<int> list = {1, 2, 3, 4, 5};
  std::vector<int> vec = {6, 7, 8, 9, 10};
  list.remove(3);
  for (int &i : list) {
    std::cout << i << " ";
  }
  std::cout << "\n";
  vec.insert(vec.begin(), 99);
  for (int &i : vec) {
    std::cout << i << " ";
  }
  return 0;
}
