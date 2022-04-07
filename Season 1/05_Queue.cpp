#include <iostream>
#include "./05_Queue.h"
#include "./Person.h"

int main()
{
    Queue<Person> queue = Queue<Person>();
    queue.en_queue(std::make_shared<Person>(10, "Alice0"));
    queue.en_queue(std::make_shared<Person>(11, "Alice1"));
    queue.en_queue(std::make_shared<Person>(12, "Alice2"));
    queue.en_queue(std::make_shared<Person>(13, "Alice3"));
    queue.en_queue(std::make_shared<Person>(14, "Alice4"));
    std::cout << "----------Test operator<<()----------\n";
    std::cout << queue;
    std::cout << "----------Test front()----------\n";
    std::cout << "front: " << *queue.front();
    std::cout << "----------Test de_queue()----------\n";
    std::cout << "size=" << queue.size() << std::endl;
    while (!queue.is_empty())
        std::cout << *queue.de_queue();
    std::cout << "size=" << queue.size() << std::endl;
    return 0;
}

/*
2022年4月5日 23:19:03
输出:
----------Test front()----------
front: 0x686710[10, Alice0]
----------Test de_queue()----------
size=5
0x686710[10, Alice0]
delete 0x686710[10, Alice0]
0x686780[11, Alice1]
delete 0x686780[11, Alice1]
0x6867f0[12, Alice2]
delete 0x6867f0[12, Alice2]
0x686860[13, Alice3]
delete 0x686860[13, Alice3]
0x6868d0[14, Alice4]
delete 0x6868d0[14, Alice4]
size=0
*/