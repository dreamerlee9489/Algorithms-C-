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
    return 0;
}

/*
输出:
delete 0x2521de0[10, Alice10]
delete 0x25221a0[109, Alice109]
delete 0x2522330[9, Alice9]
delete 0x25222e0[108, Alice108]
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
delete 0x2521ed0[12, Alice12]
[11, Alice11]
delete 0x2522380[11, Alice11]
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
*/