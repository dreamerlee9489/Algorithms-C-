#include "./13_LinkedHashSet.hpp"
#include "./Person.hpp"

using namespace app;

int main(int argc, char const *argv[]) {
  LinkedHashSet<Person> set;
  set.add(make_shared<Person>(12, "Alice12"));
  set.add(make_shared<Person>(10, "Alice10"));
  set.add(make_shared<Person>(7, "Alice17"));
  set.add(make_shared<Person>(11, "Alice11"));
  set.add(make_shared<Person>(10, "Alice10"));
  set.add(make_shared<Person>(11, "Alice11"));
  set.add(make_shared<Person>(9, "Alice19"));
  set.traverse([](shared_ptr<Person> data, shared_ptr<bool> test) {
    cout << "lamdba: " << *data << "\n";
    return false;
  });
  return 0;
}

/*
delete 0xe26870[10, Alice10]
delete 0xe26a30[11, Alice11]
lamdba: [12, Alice12]
lamdba: [10, Alice10]
lamdba: [7, Alice17]
lamdba: [11, Alice11]
lamdba: [9, Alice19]
delete 0xe26a30[9, Alice19]
delete 0xe26b10[10, Alice10]
delete 0xe26870[11, Alice11]
delete 0xe26950[7, Alice17]
delete 0xe26790[12, Alice12]
*/