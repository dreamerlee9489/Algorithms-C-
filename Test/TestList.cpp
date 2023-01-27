#include <iostream>
#include <iterator>
#include <list>
#include <vector>

int main(int argc, char const *argv[]) {
  std::list<int> list = {1, 2, 3, 4, 5, 15, 20};
  std::vector<int> vec = {6, 7, 8, 9, 10};
  // list.remove(3);
  // for (int &i : list) {
  //   std::cout << i << " ";
  // }
  // std::cout << "\n";
  // vec.insert(vec.begin(), 99);
  // for (int &i : vec) {
  //   std::cout << i << " ";
  // }
  std::list<int>::iterator iter = std::prev(list.end());
  list.emplace_back(100);
  ++iter;
  list.emplace_back(120);
  std::cout << "*end = " << *iter << "\n";
  return 0;
}
