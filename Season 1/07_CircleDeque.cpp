#include <string>
#include "./07_CircleDeque.h"
#include "./Person.h"
using namespace std;

int main()
{
    CircleDeque<Person> deque;
    for (size_t i = 0; i < 10; ++i)
    {
        deque.push_front(make_shared<Person>(i + 1, "Alice" + to_string(i + 1)));
        deque.push(make_shared<Person>(i + 100, "Alice" + to_string(i + 100)));
    }
    for (size_t i = 0; i < 3; ++i)
    {
        deque.pop();
        deque.pop_rear();
    }
    deque.push_front(make_shared<Person>(11, "Alice11"));
    deque.push_front(make_shared<Person>(12, "Alice12"));
    cout << "size=" << deque.size() << ", capacity=" << deque.capacity() << "\n";
    cout << "----------Test operator<<()----------\n";
    cout << deque;
    cout << "----------Test pop()----------\n";
    while (!deque.is_empty())
        cout << *deque.pop() << "\n";
    std::getchar();
    return 0;
}

/*
delete 0xd42230[10, Alice10]
delete 0xd41d50[109, Alice109]
delete 0xd42410[9, Alice9]
delete 0xd42350[108, Alice108]
delete 0xea6d40[8, Alice8]
delete 0xea6da0[107, Alice107]
size=16, capacity=32
----------Test operator<<()----------
[11, Alice11]
[7, Alice7]
[6, Alice6]
[5, Alice5]
[4, Alice4]
[3, Alice3]
[2, Alice2]
[1, Alice1]
[100, Alice100]
[101, Alice101]
[102, Alice102]
[103, Alice103]
[104, Alice104]
[105, Alice105]
[106, Alice106]
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
nullptr
[12, Alice12]
----------Test pop()----------
[12, Alice12]
delete 0xd42410[12, Alice12]
[11, Alice11]
delete 0xd42350[11, Alice11]
[7, Alice7]
delete 0xea6c80[7, Alice7]
[6, Alice6]
delete 0xea6bc0[6, Alice6]
[5, Alice5]
delete 0xea6a50[5, Alice5]
[4, Alice4]
delete 0xea6990[4, Alice4]
[3, Alice3]
delete 0xea68d0[3, Alice3]
[2, Alice2]
delete 0xea6810[2, Alice2]
[1, Alice1]
delete 0xea6750[1, Alice1]
[100, Alice100]
delete 0xea67b0[100, Alice100]
[101, Alice101]
delete 0xea6870[101, Alice101]
[102, Alice102]
delete 0xea6930[102, Alice102]
[103, Alice103]
delete 0xea69f0[103, Alice103]
[104, Alice104]
delete 0xea66c0[104, Alice104]
[105, Alice105]
delete 0xea6c20[105, Alice105]
[106, Alice106]
delete 0xea6ce0[106, Alice106]
*/