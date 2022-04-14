#include "./09_AVLTree.h"
#include "./Person.h"

int main()
{
    AVLTree<Person> tree = AVLTree<Person>();
    std::cout << "----------Test add()----------\n";
    tree.add(std::make_shared<Person>(55, "Alice01"));
    tree.add(std::make_shared<Person>(87, "Alice02"));
    tree.add(std::make_shared<Person>(56, "Alice03"));
    tree.add(std::make_shared<Person>(74, "Alice04"));
    tree.add(std::make_shared<Person>(96, "Alice05"));
    tree.add(std::make_shared<Person>(22, "Alice06"));
    tree.add(std::make_shared<Person>(62, "Alice07"));
    tree.add(std::make_shared<Person>(20, "Alice08"));
    tree.add(std::make_shared<Person>(70, "Alice09"));
    tree.add(std::make_shared<Person>(68, "Alice10"));
    tree.add(std::make_shared<Person>(90, "Alice11"));
    tree.add(std::make_shared<Person>(50, "Alice12"));
    std::cout << "height: " << tree.height() << "\n";
    std::cout << tree;
    std::cout << "----------Test remove()----------\n";
    tree.remove(std::make_shared<Person>(55, "Alice01"));
    tree.remove(std::make_shared<Person>(87, "Alice02"));
    tree.remove(std::make_shared<Person>(56, "Alice03"));
    std::cout << "height: " << tree.height() << "\n";
    std::cout << tree;
    std::cout << "----------Test AVLTree(const AVLTree<T> &)----------\n";
    AVLTree<Person> tree2 = AVLTree<Person>(tree);
    std::cout << tree2;
    std::cout << "----------Test AVLTree(AVLTree<T> &&)----------\n";
    AVLTree<Person> tree3 = AVLTree<Person>(std::move(tree));
    std::cout << tree3;
    return 0;
}

/*
2022年4月11日 20:24:12
----------Test add()----------
height: 5
[70, Alice09] h=5
[56, Alice03] h=4       [87, Alice02] h=3
[22, Alice06] h=3       [62, Alice07] h=2       [74, Alice04] h=1       [96, Alice05] h=2
[20, Alice08] h=1       [55, Alice01] h=2       [68, Alice10] h=1       [90, Alice11] h=1
[50, Alice12] h=1

----------Test remove()----------
delete 0xd66660[55, Alice01]
delete 0xd66d20[55, Alice01]
delete 0xd666f0[87, Alice02]
delete 0xd66660[87, Alice02]
delete 0xd66780[56, Alice03]
delete 0xd66660[56, Alice03]
height: 4
[70, Alice09] h=4
[62, Alice07] h=3       [90, Alice11] h=2
[22, Alice06] h=2       [68, Alice10] h=1       [74, Alice04] h=1       [96, Alice05] h=1
[20, Alice08] h=1       [50, Alice12] h=1

----------Test operator=(const AVLTree<T>&)----------
[70, Alice09] h=4
[62, Alice07] h=3       [90, Alice11] h=2
[22, Alice06] h=2       [68, Alice10] h=1       [74, Alice04] h=1       [96, Alice05] h=1
[20, Alice08] h=1       [50, Alice12] h=1

----------Test operator=(AVLTree<T>&&)----------
[70, Alice09] h=4
[62, Alice07] h=3       [90, Alice11] h=2
[22, Alice06] h=2       [68, Alice10] h=1       [74, Alice04] h=1       [96, Alice05] h=1
[20, Alice08] h=1       [50, Alice12] h=1

delete 0xd66a50[20, Alice08]
delete 0xd66c90[50, Alice12]
delete 0xd66930[22, Alice06]
delete 0xd66b70[68, Alice10]
delete 0xd669c0[62, Alice07]
delete 0xd66810[74, Alice04]
delete 0xd668a0[96, Alice05]
delete 0xd66c00[90, Alice11]
delete 0xd66ae0[70, Alice09]
*/