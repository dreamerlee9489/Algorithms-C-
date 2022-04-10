#include <iostream>
#include "./06_BinarySearchTree.h"
#include "./Person.h"

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
    std::cout << "----------Test traverse()----------\n";
    tree.traverse(BinarySearchTree<Person>::TraverseOrder::Level, [](std::shared_ptr<Person> data)
                  { std::cout << "lambda: " << *data << "\n"; });
    std::cout << "height=" << tree.height() << "\n";
    std::cout << "----------Test is_complete()----------\n";
    std::cout << "is complete: " << tree.is_complete() << "\n";
    tree.clear();
    tree.add(std::make_shared<Person>(7, "Alice7"));
    tree.add(std::make_shared<Person>(4, "Alice4"));
    tree.add(std::make_shared<Person>(9, "Alice9"));
    tree.add(std::make_shared<Person>(2, "Alice2"));
    tree.add(std::make_shared<Person>(5, "Alice5"));
    std::cout << "height=" << tree.height() << "\n";
    std::cout << "is complete: " << tree.is_complete() << "\n";
    std::cout << "----------Test operator<<()----------\n";
    std::cout << tree;

    return 0;
}

/*
2022年4月9日 12:01:06
输出：
----------Test traverse()----------
lambda: [7, Alice7]
lambda: [4, Alice4]
lambda: [9, Alice9]
lambda: [2, Alice2]
lambda: [5, Alice5]
lambda: [8, Alice8]
lambda: [11, Alice11]
lambda: [1, Alice1]
lambda: [3, Alice3]
lambda: [10, Alice10]
lambda: [12, Alice12]
height=4
----------Test is_complete()----------
is complete: 0
delete 0x1d6810[1, Alice1]
delete 0x1d6890[3, Alice3]
delete 0x1d6790[2, Alice2]
delete 0x1d6910[5, Alice5]
delete 0x1d6710[4, Alice4]
delete 0x1d6a10[8, Alice8]
delete 0x1d6b10[10, Alice10]
delete 0x1d6b90[12, Alice12]
delete 0x1d6a90[11, Alice11]
delete 0x1d6990[9, Alice9]
delete 0x1d6690[7, Alice7]
height=3
is complete: 1
----------Test operator<<()----------
                                                        [7, Alice7]
                        [4, Alice4]                                                [9, Alice9]
             [2, Alice2]                          [5, Alice5]
delete 0x1d6810[2, Alice2]
delete 0x1d6890[5, Alice5]
delete 0x1d6710[4, Alice4]
delete 0x1d6790[9, Alice9]
delete 0x1d6690[7, Alice7]
*/