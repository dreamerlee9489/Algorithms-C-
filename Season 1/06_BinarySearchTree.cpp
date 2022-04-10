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
    std::cout << "----------Test operator<<()----------\n";
    std::cout << tree;
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

    return 0;
}

/*
2022年4月9日 12:01:06
输出：
----------Test operator<<()----------
                                                        [7, Alice7]
                        [4, Alice4]                                                [9, Alice9]
        [2, Alice2]                [5, Alice5]                [8, Alice8]                [11, Alice11]
[1, Alice1][3, Alice3]                                                                [10, Alice10][12, Alice12]

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
delete 0x1d68c0[1, Alice1]
delete 0x1d6940[3, Alice3]
delete 0x1d6840[2, Alice2]
delete 0x1d69c0[5, Alice5]
delete 0x1d67c0[4, Alice4]
delete 0x1d6ac0[8, Alice8]
delete 0x1d6bc0[10, Alice10]
delete 0x1d6c40[12, Alice12]
delete 0x1d6b40[11, Alice11]
delete 0x1d6a40[9, Alice9]
delete 0x1d6740[7, Alice7]
height=3
is complete: 1
delete 0x1d68c0[2, Alice2]
delete 0x1d6940[5, Alice5]
delete 0x1d67c0[4, Alice4]
delete 0x1d6840[9, Alice9]
delete 0x1d6740[7, Alice7]
*/