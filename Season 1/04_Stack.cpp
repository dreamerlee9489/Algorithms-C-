#include <iostream>
#include "./04_Stack.h"
#include "./Person.h"

int main()
{
    Stack<Person> stack = Stack<Person>();
    stack.push(std::make_shared<Person>(10, "Alice0"));
    stack.push(std::make_shared<Person>(11, "Alice1"));
    stack.push(std::make_shared<Person>(12, "Alice2"));
    stack.push(std::make_shared<Person>(13, "Alice3"));
    stack.push(std::make_shared<Person>(14, "Alice4"));
    std::cout << "----------Test operator<<()----------\n";
    std::cout << stack;
    std::cout << "----------Test top()----------\n";
    std::cout << "top: " << *stack.top() << "\n";
    std::cout << "----------Test pop()----------\n";
    std::cout << "size=" << stack.size() << std::endl;
    while (!stack.is_empty())
        std::cout << *stack.pop() << "\n";
    std::cout << "size=" << stack.size() << std::endl;
    return 0;
}

/*
2022年4月5日 16:44:41
输出:
----------Test top()----------
top: 0x6b6880[14, Alice4]
----------Test pop()----------
size=5
0x6b6880[14, Alice4]
delete 0x6b6880[14, Alice4]
0x6b6840[13, Alice3]
delete 0x6b6840[13, Alice3]
0x6b6800[12, Alice2]
delete 0x6b6800[12, Alice2]
0x6b67c0[11, Alice1]
delete 0x6b67c0[11, Alice1]
0x6b6780[10, Alice0]
size=0
delete 0x6b6780[10, Alice0]
*/