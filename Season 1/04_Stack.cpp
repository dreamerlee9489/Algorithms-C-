#include "./04_Stack.hpp"
#include "./Person.hpp"
using namespace app;

int main()
{
    Stack<Person> stack;
    stack.push(make_shared<Person>(10, "Alice0"));
    stack.push(make_shared<Person>(11, "Alice1"));
    stack.push(make_shared<Person>(12, "Alice2"));
    stack.push(make_shared<Person>(13, "Alice3"));
    stack.push(make_shared<Person>(14, "Alice4"));
    cout << "----------Test operator<<()----------\n";
    cout << stack;
    cout << "----------Test top()----------\n";
    cout << "top: " << *stack.top() << "\n";
    cout << "----------Test pop()----------\n";
    cout << "size=" << stack.size() << endl;
    while (!stack.is_empty())
        cout << *stack.pop() << "\n";
    cout << "size=" << stack.size() << endl;
    return 0;
}

/*
----------Test operator<<()----------
[10, Alice0]
[11, Alice1]
[12, Alice2]
[13, Alice3]
[14, Alice4]
----------Test top()----------
top: [14, Alice4]
----------Test pop()----------
size=5
[14, Alice4]
delete 0x6d68f0[14, Alice4]
[13, Alice3]
delete 0x6d68a0[13, Alice3]
[12, Alice2]
delete 0x6d6850[12, Alice2]
[11, Alice1]
delete 0x6d6800[11, Alice1]
[10, Alice0]
delete 0x6d67b0[10, Alice0]
size=0
PS D:\M
*/