#include <string>
#include "./05_CircleDeque.h"
#include "./Person.h"

int main()
{
    CircleDeque<Person> deque = CircleDeque<Person>();
    for (size_t i = 0; i < 10; ++i)
    {
        deque.enqueue_front(std::make_shared<Person>(i + 1, "Alice" + std::to_string(i + 1)));
        deque.enqueue(std::make_shared<Person>(i + 100, "Alice" + std::to_string(i + 100)));
    }
    for (size_t i = 0; i < 3; ++i)
    {
        deque.dequeue();
        deque.dequeue_rear();
    }
    deque.enqueue_front(std::make_shared<Person>(11, "Alice11"));
    deque.enqueue_front(std::make_shared<Person>(12, "Alice12"));
    std::cout << "size=" << deque.size() << ", capacity=" << deque.capacity() << "\n";
    std::cout << "----------Test operator<<()----------\n";
    std::cout << deque;
    std::cout << "----------Test de_queue()----------\n";
    while (!deque.is_empty())
        std::cout << *deque.dequeue();

    return 0;
}

/*
2022年4月8日 00:29:05
输出:
----------Test de_queue() / de_queue_rear()----------
delete 0xed1db0[10, Alice10]
delete 0xed21b0[109, Alice109]
delete 0xed1fb0[9, Alice9]
delete 0xed20f0[108, Alice108]
size=16, capacity=32
----------Test operator<<()----------
0xed2370[11, Alice11]
0x1066b30[7, Alice7]
0x1066ab0[6, Alice6]
0x1066920[5, Alice5]
0x10668a0[4, Alice4]
0x1066820[3, Alice3]
0x10667a0[2, Alice2]
0x1066720[1, Alice1]
0x1066760[100, Alice100]
0x10667e0[101, Alice101]
0x1066860[102, Alice102]
0x10668e0[103, Alice103]
0x1066a70[104, Alice104]
0x1066af0[105, Alice105]
0x1066b70[106, Alice106]
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
0xed1f30[12, Alice12]
----------Test de_queue()----------
0xed1f30[12, Alice12]
delete 0xed1f30[12, Alice12]
0xed2370[11, Alice11]
delete 0xed2370[11, Alice11]
0x1066b30[7, Alice7]
0x1066ab0[6, Alice6]
0x1066920[5, Alice5]
0x10668a0[4, Alice4]
0x1066820[3, Alice3]
0x10667a0[2, Alice2]
0x1066720[1, Alice1]
0x1066760[100, Alice100]
0x10667e0[101, Alice101]
0x1066860[102, Alice102]
0x10668e0[103, Alice103]
0x1066a70[104, Alice104]
0x1066af0[105, Alice105]
0x1066b70[106, Alice106]
*/