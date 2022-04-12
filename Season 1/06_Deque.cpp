#include "./06_Deque.h"
#include "./Person.h"

int main(int argc, char const *argv[])
{
    Deque<Person> deque = Deque<Person>();
    deque.push(std::make_shared<Person>(10, "Alice10"));
    deque.push(std::make_shared<Person>(11, "Alice11"));
    deque.push(std::make_shared<Person>(12, "Alice12"));
    deque.push_front(std::make_shared<Person>(13, "Alice13"));
    deque.push_front(std::make_shared<Person>(14, "Alice14"));
    deque.push_front(std::make_shared<Person>(15, "Alice15"));
    std::cout << "----------Test operator<<()----------\n";
    std::cout << deque;
    size_t size = deque.size();
    std::cout << "size=" << size << "\n";
    std::cout << "----------Test pop()----------\n";
    for(size_t i = 0; i < size / 2; ++i)
        std::cout << *deque.pop();
    std::cout << "----------Test pop_rear()----------\n";
    for (size_t i = 0; i < size / 2; ++i)
        std::cout << *deque.pop_rear();
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
----------Test pop()----------
0x1d6940[15, Alice15]
delete 0x1d6940[15, Alice15]
0x1d68d0[14, Alice14]
delete 0x1d68d0[14, Alice14]
0x1d6860[13, Alice13]
delete 0x1d6860[13, Alice13]
----------Test pop_rear()----------
0x1d67f0[12, Alice12]
delete 0x1d67f0[12, Alice12]
0x1d6780[11, Alice11]
delete 0x1d6780[11, Alice11]
0x1d6710[10, Alice10]
delete 0x1d6710[10, Alice10]
size=0
*/