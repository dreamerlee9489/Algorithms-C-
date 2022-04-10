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
    std::cout << "----------Test traverse(Level)----------\n";
    tree.traverse(BinarySearchTree<Person>::TraverseOrder::Level, [](std::shared_ptr<Person> data)
    { 
        std::cout << "lambda: " << *data << "\n"; 
    });
    std::cout << "height=" << tree.height() << "\n";
    std::cout << "is complete: " << tree.is_complete() << "\n";
    std::cout << "----------Test remove()----------\n";
    tree.remove(std::make_shared<Person>(7, "Alice7"));
    tree.remove(std::make_shared<Person>(2, "Alice2"));
    tree.remove(std::make_shared<Person>(9, "Alice9"));
    tree.traverse(BinarySearchTree<Person>::TraverseOrder::In);
    std::cout << "----------Test clear()----------\n";
    tree.clear();
    tree.add(std::make_shared<Person>(7, "Alice7"));
    tree.add(std::make_shared<Person>(4, "Alice4"));
    tree.add(std::make_shared<Person>(9, "Alice9"));
    tree.add(std::make_shared<Person>(2, "Alice2"));
    tree.add(std::make_shared<Person>(5, "Alice5"));
    std::cout << "----------Test operator<<()----------\n";
    std::cout << tree;
    std::cout << "----------Test traverse(In)----------\n";
    tree.traverse(BinarySearchTree<Person>::TraverseOrder::In);
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

----------Test traverse(Level)----------
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
is complete: 0
----------Test remove()----------
delete 0xf86690[7, Alice7]
delete 0xf86c10[7, Alice7]
delete 0xf86790[2, Alice2]
delete 0xf86690[2, Alice2]
delete 0xf86990[9, Alice9]
delete 0xf86690[9, Alice9]
[1, Alice1]
[3, Alice3]
[4, Alice4]
[5, Alice5]
[8, Alice8]
[10, Alice10]
[11, Alice11]
[12, Alice12]
----------Test clear()----------
delete 0xf86810[1, Alice1]
delete 0xf86890[3, Alice3]
delete 0xf86910[5, Alice5]
delete 0xf86710[4, Alice4]
delete 0xf86b10[10, Alice10]
delete 0xf86b90[12, Alice12]
delete 0xf86a90[11, Alice11]
delete 0xf86a10[8, Alice8]
----------Test operator<<()----------
                        [7, Alice7]
        [4, Alice4]                [9, Alice9]
[2, Alice2][5, Alice5]

----------Test traverse(In)----------
[2, Alice2]
[4, Alice4]
[5, Alice5]
[7, Alice7]
[9, Alice9]
height=3
is complete: 1
delete 0xf86810[2, Alice2]
delete 0xf86890[5, Alice5]
delete 0xf86710[4, Alice4]
delete 0xf86790[9, Alice9]
delete 0xf86690[7, Alice7]
*/