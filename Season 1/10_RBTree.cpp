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

    return 0;
}

/*
2022年4月13日 16:43:35
输出：
----------Test add()----------
height: 5
[70, Alice09] BLACK
[56, Alice03] BLACK     [87, Alice02] BLACK
[22, Alice06] RED       [62, Alice07] BLACK     [74, Alice04] BLACK     [96, Alice05] BLACK
[20, Alice08] BLACK     [55, Alice01] BLACK     [68, Alice10] RED       [90, Alice11] RED
[50, Alice12] RED

----------Test remove()----------
delete 0x1016660[55, Alice01]
delete 0x1016d20[55, Alice01]
delete 0x10166f0[87, Alice02]
delete 0x1016660[87, Alice02]
delete 0x1016780[56, Alice03]
delete 0x1016660[56, Alice03]
height: 4
[70, Alice09] BLACK
[62, Alice07] BLACK     [90, Alice11] BLACK
[22, Alice06] RED       [68, Alice10] BLACK     [74, Alice04] BLACK     [96, Alice05] BLACK
[20, Alice08] BLACK     [50, Alice12] BLACK

delete 0x1016a50[20, Alice08]
delete 0x1016c90[50, Alice12]
delete 0x1016930[22, Alice06]
delete 0x1016b70[68, Alice10]
delete 0x10169c0[62, Alice07]
delete 0x1016810[74, Alice04]
delete 0x10168a0[96, Alice05]
delete 0x1016c00[90, Alice11]
delete 0x1016ae0[70, Alice09]
*/