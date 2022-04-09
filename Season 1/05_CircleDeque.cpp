#include <string>
#include "./05_CircleDeque.h"
#include "./Person.h"

int main()
{
    CircleDeque<Person> deque = CircleDeque<Person>();
    for (size_t i = 0; i < 10; ++i)
    {
        deque.push_front(std::make_shared<Person>(i + 1, "Alice" + std::to_string(i + 1)));
        deque.push(std::make_shared<Person>(i + 100, "Alice" + std::to_string(i + 100)));
    }
    for (size_t i = 0; i < 3; ++i)
    {
        deque.pop();
        deque.pop_rear();
    }
    deque.push_front(std::make_shared<Person>(11, "Alice11"));
    deque.push_front(std::make_shared<Person>(12, "Alice12"));
    std::cout << "size=" << deque.size() << ", capacity=" << deque.capacity() << "\n";
    std::cout << "----------Test operator<<()----------\n";
    std::cout << deque;
    std::cout << "----------Test pop()----------\n";
    while (!deque.is_empty())
        std::cout << *deque.pop() << "\n";

    return 0;
}

/*
2022年4月8日 00:29:05
输出:
delete 0x26520b0[10, Alice10]
delete 0x2651eb0[109, Alice109]
delete 0x2651e70[9, Alice9]
delete 0x26523b0[108, Alice108]
size=16, capacity=32
----------Test operator<<()----------
0x2652170[11, Alice11]
0xe96be0[7, Alice7]
0xe96b60[6, Alice6]
0xe969d0[5, Alice5]
0xe96950[4, Alice4]
0xe968d0[3, Alice3]
0xe96850[2, Alice2]
0xe967d0[1, Alice1]
0xe96810[100, Alice100]
0xe96890[101, Alice101]
0xe96910[102, Alice102]
0xe96990[103, Alice103]
0xe96b20[104, Alice104]
0xe96ba0[105, Alice105]
0xe96c20[106, Alice106]
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
0x2651eb0[12, Alice12]
----------Test pop()----------
0x2651eb0[12, Alice12]
delete 0x2651eb0[12, Alice12]
0x2652170[11, Alice11]
delete 0x2652170[11, Alice11]
0xe96be0[7, Alice7]
0xe96b60[6, Alice6]
0xe969d0[5, Alice5]
0xe96950[4, Alice4]
0xe968d0[3, Alice3]
0xe96850[2, Alice2]
0xe967d0[1, Alice1]
0xe96810[100, Alice100]
0xe96890[101, Alice101]
0xe96910[102, Alice102]
0xe96990[103, Alice103]
0xe96b20[104, Alice104]
0xe96ba0[105, Alice105]
0xe96c20[106, Alice106]
*/