#include "./11_Set.h"
#include "./Person.h"
using namespace std;

int main(int argc, char const *argv[])
{
    Set<Person> tree = Set<Person>([](shared_ptr<Person> a, shared_ptr<Person> b)
    {
        if((*a)._age < (*b)._age)
            return -1;
        else if ((*a)._age > (*b)._age)
            return 1;
        return 0;
    });
    tree.add(make_shared<Person>(12, "Alice12"));
    tree.add(make_shared<Person>(10, "Alice10"));
    tree.add(make_shared<Person>(7, "Alice17"));
    tree.add(make_shared<Person>(11, "Alice11"));
    tree.add(make_shared<Person>(10, "Alice10"));
    tree.add(make_shared<Person>(11, "Alice11"));
    tree.add(make_shared<Person>(9, "Alice19"));
    tree.traverse([](shared_ptr<Person> data)
    {
        cout << "lamdba: " << *data << "\n";
        return false;
    });
    return 0;
}

/*
输出：
delete 0x6e6770[10, Alice10]
delete 0x6e6890[11, Alice11]
lamdba: [7, Alice17]
lamdba: [9, Alice19]
lamdba: [10, Alice10]
lamdba: [11, Alice11]
lamdba: [12, Alice12]
delete 0x6e6890[9, Alice19]
delete 0x6e6800[7, Alice17]
delete 0x6e6770[11, Alice11]
delete 0x6e66e0[12, Alice12]
delete 0x6e6920[10, Alice10]
*/