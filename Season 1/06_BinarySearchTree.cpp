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
    tree.traverse(BinarySearchTree<Person>::TraverseOrder::Level, [](std::shared_ptr<Person> data){ 
        std::cout << "lambda: " << *data << "\n"; 
    });
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
----------Test traverse()----------
lambda: 0x6a6740[7, Alice7]
lambda: 0x6a67b0[4, Alice4]
lambda: 0x6a69e0[9, Alice9]
lambda: 0x6a6820[2, Alice2]
lambda: 0x6a6970[5, Alice5]
lambda: 0x6a6a50[8, Alice8]
lambda: 0x6a6ac0[11, Alice11]
lambda: 0x6a6890[1, Alice1]
lambda: 0x6a6900[3, Alice3]
lambda: 0x6a6b30[10, Alice10]
lambda: 0x6a6ba0[12, Alice12]
height=4
----------Test is_complete()----------
is complete: 0
delete 0x6a6890[1, Alice1]
delete 0x6a6900[3, Alice3]
delete 0x6a6820[2, Alice2]
delete 0x6a6970[5, Alice5]
delete 0x6a67b0[4, Alice4]
delete 0x6a6a50[8, Alice8]
delete 0x6a6b30[10, Alice10]
delete 0x6a6ba0[12, Alice12]
delete 0x6a6ac0[11, Alice11]
delete 0x6a69e0[9, Alice9]
delete 0x6a6740[7, Alice7]
height=3
is complete: 1
delete 0x6a6890[2, Alice2]
delete 0x6a6900[5, Alice5]
delete 0x6a67b0[4, Alice4]
delete 0x6a6820[9, Alice9]
delete 0x6a6740[7, Alice7]
*/