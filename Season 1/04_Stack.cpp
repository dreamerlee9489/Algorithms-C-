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
    while (!stack.is_empty())
        std::cout << *stack.pop();
    return 0;
}