#include "./12_HashSet.hpp"
#include "./Person.hpp"

using namespace app;

int main(int argc, char const* argv[]) {
	HashSet<Person> set;
	set.add(make_shared<Person>(12, "Alice12"));
	set.add(make_shared<Person>(10, "Alice10"));
	set.add(make_shared<Person>(7, "Alice17"));
	set.add(make_shared<Person>(11, "Alice11"));
	set.add(make_shared<Person>(10, "Alice10"));
	set.add(make_shared<Person>(11, "Alice11"));
	set.add(make_shared<Person>(9, "Alice19"));
	set.traverse([](shared_ptr<Person> data, shared_ptr<bool> test) {
		cout << "lamdba: " << *data << "\t";
		return false;
		});
	return 0;
}

/*
delete 0xd46840[10, Alice10]
delete 0xd469e0[11, Alice11]
---------- 1 ----------
lamdba: [9, Alice19]
---------- 9 ----------
lamdba: [10, Alice10]
---------- 11 ----------
lamdba: [11, Alice11]
---------- 13 ----------
lamdba: [12, Alice12]
lamdba: [7, Alice17]
delete 0xd469e0[9, Alice19]
delete 0xd46ab0[10, Alice10]
delete 0xd46840[11, Alice11]
delete 0xd46910[7, Alice17]
delete 0xd46770[12, Alice12]
*/