#include <functional>
#include <iostream>
#include <list>

typedef std::list<std::function<int(int, int)>> event_t;

int main(int argc, char const *argv[]) {
  event_t event;
  event.push_back([](int a, int b) { return a + b; });
  event.push_back([](int a, int b) { return a - b; });
  event.push_back([](int a, int b) { return a * b; });
  event.push_back([](int a, int b) { return a / b; });
  for (auto &e : event)
    std::cout << (uintptr_t)&e << ": " << e(3, 4) << "\n";
  event.clear();
  int i = 10, *j = new int(20);
  std::cout << (uintptr_t)&i << " " << (uintptr_t)j << "\n";
  return 0;
}
