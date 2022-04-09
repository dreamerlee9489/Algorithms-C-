#include <iostream>
#include "./06_BinarySearchTree.h"
#include "./Person.h"
using namespace std;

int main()
{
    BinarySearchTree<Person> tree = BinarySearchTree<Person>();
    tree.add(std::make_shared<Person>(7, "Alice7"));
    tree.add(std::make_shared<Person>(4, "Alice4"));
    tree.add(std::make_shared<Person>(2, "Alice2"));
    tree.add(std::make_shared<Person>(1, "Alice1"));
    tree.add(std::make_shared<Person>(3, "Alice3"));
    tree.add(std::make_shared<Person>(5, "Alice5"));
    tree.add(std::make_shared<Person>(9, "Alice9"));
    tree.add(std::make_shared<Person>(8, "Alice8"));
    tree.add(std::make_shared<Person>(11, "Alice11"));
    tree.add(std::make_shared<Person>(10, "Alice10"));
    tree.add(std::make_shared<Person>(12, "Alice12"));
    tree.traverse(BinarySearchTree<Person>::TraverseOrder::Level, [](std::shared_ptr<Person> data)
                  { std::cout << "lambda: " << *data; });
    return 0;
}

/*
2022年4月9日 12:01:06
输出：
lambda: 0xd6690[7, Alice7]
lambda: 0xd6700[4, Alice4]
lambda: 0xd6930[9, Alice9]
lambda: 0xd6770[2, Alice2]
lambda: 0xd68c0[5, Alice5]
lambda: 0xd69a0[8, Alice8]
lambda: 0xd6a10[11, Alice11]
lambda: 0xd67e0[1, Alice1]
lambda: 0xd6850[3, Alice3]
lambda: 0xd6a80[10, Alice10]
lambda: 0xd6af0[12, Alice12]
delete 0xd67e0[1, Alice1]
delete 0xd6850[3, Alice3]
delete 0xd6770[2, Alice2]
delete 0xd68c0[5, Alice5]
delete 0xd6700[4, Alice4]
delete 0xd69a0[8, Alice8]
delete 0xd6a80[10, Alice10]
delete 0xd6af0[12, Alice12]
delete 0xd6a10[11, Alice11]
delete 0xd6930[9, Alice9]
delete 0xd6690[7, Alice7]
*/