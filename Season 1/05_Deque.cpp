#include "./05_Deque.h"
#include "./Person.h"

int main(int argc, char const *argv[])
{
    Deque<Person> deque = Deque<Person>();
    deque.enqueue(std::make_shared<Person>(10, "Alice10"));
    deque.enqueue(std::make_shared<Person>(11, "Alice11"));
    deque.enqueue(std::make_shared<Person>(12, "Alice12"));
    deque.enqueue_front(std::make_shared<Person>(13, "Alice13"));
    deque.enqueue_front(std::make_shared<Person>(14, "Alice14"));
    deque.enqueue_front(std::make_shared<Person>(15, "Alice15"));
    std::cout << "----------Test operator<<()----------\n";
    std::cout << deque;
    size_t size = deque.size();
    std::cout << "size=" << size << "\n";
    std::cout << "----------Test de_queue()----------\n";
    for(size_t i = 0; i < size / 2; ++i)
        std::cout << *deque.dequeue();
    std::cout << "----------Test de_queue_rear()----------\n";
    for (size_t i = 0; i < size / 2; ++i)
        std::cout << *deque.dequeue_rear();
    std::cout << "size=" << deque.size() << "\n";
    return 0;
}

/*
2022年4月8日 08:28:26
输出:
----------Test operator<<()----------
0x1d6940[15, Alice15]
0x1d68d0[14, Alice14]
0x1d6860[13, Alice13]
0x1d6710[10, Alice10]
0x1d6780[11, Alice11]
0x1d67f0[12, Alice12]
size=6
----------Test de_queue()----------
0x1d6940[15, Alice15]
delete 0x1d6940[15, Alice15]
0x1d68d0[14, Alice14]
delete 0x1d68d0[14, Alice14]
0x1d6860[13, Alice13]
delete 0x1d6860[13, Alice13]
----------Test de_queue_rear()----------
0x1d67f0[12, Alice12]
delete 0x1d67f0[12, Alice12]
0x1d6780[11, Alice11]
delete 0x1d6780[11, Alice11]
0x1d6710[10, Alice10]
delete 0x1d6710[10, Alice10]
size=0
*/