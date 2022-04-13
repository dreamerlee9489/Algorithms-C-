#include "./10_RBTree.h"
#include "./Person.h"

int main()
{
    RBTree<Person> tree = RBTree<Person>();
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
    std::cout << "----------Test operator=(const RBTree<T>&)----------\n";
    RBTree<Person> tree2 = RBTree<Person>();
    tree2 = tree;
    std::cout << tree2;
    std::cout << "----------Test operator=(RBTree<T>&&)----------\n";
    RBTree<Person> tree3 = RBTree<Person>();
    tree3 = std::move(tree);
    std::cout << tree3;

    return 0;
}

/*
2022年4月13日 16:43:35
输出：
----------Test add()----------
height: 5
[70, Alice09] BLACK
[56, Alice03] BLACK     [87, Alice02] BLACK
[22, Alice06] R E D     [62, Alice07] BLACK     [74, Alice04] BLACK     [96, Alice05] BLACK
[20, Alice08] BLACK     [55, Alice01] BLACK     [68, Alice10] R E D     [90, Alice11] R E D
[50, Alice12] R E D

----------Test remove()----------
delete 0x1076730[55, Alice01]
delete 0x1076df0[55, Alice01]
delete 0x10767c0[87, Alice02]
delete 0x1076730[87, Alice02]
delete 0x1076850[56, Alice03]
delete 0x1076730[56, Alice03]
height: 4
[70, Alice09] BLACK
[62, Alice07] BLACK     [90, Alice11] BLACK
[22, Alice06] R E D     [68, Alice10] BLACK     [74, Alice04] BLACK     [96, Alice05] BLACK
[20, Alice08] BLACK     [50, Alice12] BLACK

----------Test operator=(const RBTree<T>&)----------
[70, Alice09] BLACK
[62, Alice07] R E D     [90, Alice11] BLACK
[22, Alice06] BLACK     [68, Alice10] BLACK     [74, Alice04] R E D     [96, Alice05] R E D
[20, Alice08] R E D     [50, Alice12] R E D

----------Test operator=(RBTree<T>&&)----------
[70, Alice09] BLACK
[62, Alice07] BLACK     [90, Alice11] BLACK
[22, Alice06] R E D     [68, Alice10] BLACK     [74, Alice04] BLACK     [96, Alice05] BLACK
[20, Alice08] BLACK     [50, Alice12] BLACK

delete 0x1076b20[20, Alice08]
delete 0x1076d60[50, Alice12]
delete 0x1076a00[22, Alice06]
delete 0x1076c40[68, Alice10]
delete 0x1076a90[62, Alice07]
delete 0x10768e0[74, Alice04]
delete 0x1076970[96, Alice05]
delete 0x1076cd0[90, Alice11]
delete 0x1076bb0[70, Alice09]
*/