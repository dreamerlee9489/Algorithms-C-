#include "./06_BST.h"
#include "./Person.h"

int main()
{
    BST<Person> tree = BST<Person>();
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
    tree.traverse(BST<Person>::TraverseOrder::Level, [](std::shared_ptr<Person> data)
                   { std::cout << "lambda: " << *data << "\n"; });
    std::cout << "height=" << tree.height() << "\n";
    std::cout << "is complete: " << tree.is_complete() << "\n";
    std::cout << "----------Test remove()----------\n";
    tree.remove(std::make_shared<Person>(7, "Alice7"));
    tree.remove(std::make_shared<Person>(2, "Alice2"));
    tree.remove(std::make_shared<Person>(9, "Alice9"));
    tree.traverse(BST<Person>::TraverseOrder::In);
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
    tree.traverse(BST<Person>::TraverseOrder::In);
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
delete 0x6f6660[7, Alice7]
delete 0x6f6be0[7, Alice7]
delete 0x6f6760[2, Alice2]
delete 0x6f6660[2, Alice2]
delete 0x6f6960[9, Alice9]
delete 0x6f6660[9, Alice9]
[1, Alice1]
[3, Alice3]
[4, Alice4]
[5, Alice5]
[8, Alice8]
[10, Alice10]
[11, Alice11]
[12, Alice12]
----------Test clear()----------
delete 0x6f67e0[1, Alice1]
delete 0x6f6860[3, Alice3]
delete 0x6f68e0[5, Alice5]
delete 0x6f66e0[4, Alice4]
delete 0x6f6ae0[10, Alice10]
delete 0x6f6b60[12, Alice12]
delete 0x6f6a60[11, Alice11]
delete 0x6f69e0[8, Alice8]
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
delete 0x6f67e0[2, Alice2]
delete 0x6f6860[5, Alice5]
delete 0x6f66e0[4, Alice4]
delete 0x6f6760[9, Alice9]
delete 0x6f6660[7, Alice7]
*/