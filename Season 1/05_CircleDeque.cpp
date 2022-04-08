#include <string>
#include "./05_CircleDeque.h"
#include "./Person.h"

int main()
{
    CircleDeque<Person> deque = CircleDeque<Person>();
    for(size_t i = 0; i < 10; ++i)
    {
        deque.enqueue_front(std::make_shared<Person>(i + 1, "Alice" + std::to_string(i + 1)));
        deque.enqueue(std::make_shared<Person>(i + 100, "Alice" + std::to_string(i + 100)));
    }
    std::cout << "----------Test de_queue() / de_queue_rear()----------\n";
    for(size_t i = 0; i < 3; ++i)
    {
        deque.dequeue();
        deque.dequeue_rear();
    }
    deque.enqueue_front(std::make_shared<Person>(11, "Alice11"));
    deque.enqueue_front(std::make_shared<Person>(12, "Alice12"));
    std::cout << "size=" << deque.size() << ", capacity=" << deque.capacity() << "\n";
    std::cout << "----------Test operator<<()----------\n";
    std::cout << deque;

    return 0;
}

/*
2022年4月8日 00:29:05
输出:
----------Test de_queue() / de_queue_rear()----------
delete 0xe023f0[10, Alice10]
delete 0xe01e30[109, Alice109]
delete 0xe02270[9, Alice9]
delete 0xe023b0[108, Alice108]
size=16, capacity=32
----------Test operator<<()----------
0xe021f0[11, Alice11]
0xf26b90[7, Alice7]
0xf26b10[6, Alice6]
0xf26980[5, Alice5]
0xf26900[4, Alice4]
0xf26880[3, Alice3]
0xf26800[2, Alice2]
0xf26780[1, Alice1]
0xf267c0[100, Alice100]
0xf26840[101, Alice101]
0xf268c0[102, Alice102]
0xf26940[103, Alice103]
0xf26ad0[104, Alice104]
0xf26b50[105, Alice105]
0xf26bd0[106, Alice106]
delete 0xe021f0[11, Alice11]
delete 0xe01eb0[12, Alice12]
*/