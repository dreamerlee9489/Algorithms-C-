#include "./05_Queue.hpp"
#include "./Person.hpp"

using namespace app;

int main() {
	Queue<Person> queue;
	queue.push(make_shared<Person>(10, "Alice0"));
	queue.push(make_shared<Person>(11, "Alice1"));
	queue.push(make_shared<Person>(12, "Alice2"));
	queue.push(make_shared<Person>(13, "Alice3"));
	queue.push(make_shared<Person>(14, "Alice4"));
	cout << "----------Test operator<<()----------\n";
	cout << queue;
	cout << "----------Test front()----------\n";
	cout << "front: " << *queue.front() << "\n";
	cout << "----------Test pop()----------\n";
	cout << "size=" << queue.size() << endl;
	while (!queue.is_empty())
		cout << *queue.pop() << "\n";
	cout << "size=" << queue.size() << endl;
	return 0;
}

/*
----------Test operator<<()----------
[10, Alice0]
[11, Alice1]
[12, Alice2]
[13, Alice3]
[14, Alice4]
----------Test front()----------
front: [10, Alice0]
----------Test pop()----------
size=5
[10, Alice0]
delete 0x6d6740[10, Alice0]
[11, Alice1]
delete 0x6d67c0[11, Alice1]
[12, Alice2]
delete 0x6d6840[12, Alice2]
[13, Alice3]
delete 0x6d68c0[13, Alice3]
[14, Alice4]
delete 0x6d6940[14, Alice4]
size=0
*/