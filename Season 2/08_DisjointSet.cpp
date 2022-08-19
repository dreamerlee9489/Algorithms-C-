#include "./08_DisjointSet.hpp"
#include "./Person.hpp"

using namespace std;
using namespace app;

int main(int argc, char const *argv[]) {
  DisjointSet<Person> set;
  size_t count = 20;
  for (size_t i = 0; i < count; ++i)
    set.add(new Person(i));
  set.union_set(new Person(0), new Person(1));
  set.union_set(new Person(0), new Person(3));
  set.union_set(new Person(0), new Person(4));
  set.union_set(new Person(2), new Person(3));
  set.union_set(new Person(2), new Person(5));
  set.union_set(new Person(6), new Person(7));
  set.union_set(new Person(8), new Person(10));
  set.union_set(new Person(9), new Person(10));
  set.union_set(new Person(9), new Person(11));
  cout << "is_same(2, 7)=" << set.is_same(new Person(2), new Person(7)) << "\n";
  set.union_set(new Person(4), new Person(6));
  cout << "is_same(2, 7)=" << set.is_same(new Person(2), new Person(7)) << "\n";
  return 0;
}

/*
输出：
is_same(2, 7)=0
is_same(2, 7)=1
delete 0x9e8898[19, unnamed]
delete 0x9e9468[18, unnamed]
delete 0x9e8928[17, unnamed]
delete 0x9e8808[16, unnamed]
delete 0x2612e68[4, unnamed]
delete 0x2612d68[3, unnamed]
delete 0x9e7398[5, unnamed]
delete 0x26123d8[2, unnamed]
delete 0x26120b8[0, unnamed]
delete 0x2612278[1, unnamed]
delete 0x9e7428[6, unnamed]
delete 0x9e75f8[7, unnamed]
delete 0x9e76f8[8, unnamed]
delete 0x9e77f8[9, unnamed]
delete 0x9e78f8[10, unnamed]
delete 0x9e79f8[11, unnamed]
delete 0x9e7af8[12, unnamed]
delete 0x9e7bf8[13, unnamed]
delete 0x9e7cf8[14, unnamed]
delete 0x9e7df8[15, unnamed]
*/