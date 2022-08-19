#include "./06_Deque.hpp"
#include "./Person.hpp"

using namespace app;

int main(int argc, char const *argv[]) {
  Deque<Person> deque;
  deque.push(make_shared<Person>(10, "Alice10"));
  deque.push(make_shared<Person>(11, "Alice11"));
  deque.push(make_shared<Person>(12, "Alice12"));
  deque.push_front(make_shared<Person>(13, "Alice13"));
  deque.push_front(make_shared<Person>(14, "Alice14"));
  deque.push_front(make_shared<Person>(15, "Alice15"));
  cout << "----------Test operator<<()----------\n";
  cout << deque;
  size_t size = deque.size();
  cout << "size=" << size << "\n";
  cout << "----------Test pop()----------\n";
  for (size_t i = 0; i < size / 2; ++i)
    cout << *deque.pop() << "\n";
  cout << "----------Test pop_rear()----------\n";
  for (size_t i = 0; i < size / 2; ++i)
    cout << *deque.pop_rear() << "\n";
  cout << "size=" << deque.size() << "\n";
  return 0;
}

/*
----------Test operator<<()----------
[15, Alice15]
[14, Alice14]
[13, Alice13]
[10, Alice10]
[11, Alice11]
[12, Alice12]
size=6
----------Test pop()----------
[15, Alice15]
delete 0xf769c0[15, Alice15]
[14, Alice14]
delete 0xf76940[14, Alice14]
[13, Alice13]
delete 0xf768c0[13, Alice13]
----------Test pop_rear()----------
[12, Alice12]
delete 0xf76840[12, Alice12]
[11, Alice11]
delete 0xf767c0[11, Alice11]
[10, Alice10]
delete 0xf76740[10, Alice10]
size=0
*/