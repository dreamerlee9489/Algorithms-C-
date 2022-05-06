#include "./18_PriorityQueue.h"
#include "./Person.h"
using namespace app;

int main(int argc, char const *argv[])
{
    PriorityQueue<Person> q;
    q.push(make_shared<Person>(2));
    q.push(make_shared<Person>(10));
    q.push(make_shared<Person>(5));
    q.push(make_shared<Person>(15));
    q.push(make_shared<Person>(25));
    q.push(make_shared<Person>(20));
    while (!q.is_empty())
        cout << *q.pop() << "\n";
    return 0;
}

/*
[25, unnamed]
delete 0x1e6910[25, unnamed]
[20, unnamed]
delete 0x1e6970[20, unnamed]
[15, unnamed]
delete 0x1e68b0[15, unnamed]
[10, unnamed]
delete 0x1e67f0[10, unnamed]
[5, unnamed]
delete 0x1e6850[5, unnamed]
[2, unnamed]
delete 0x1e6790[2, unnamed]
*/
