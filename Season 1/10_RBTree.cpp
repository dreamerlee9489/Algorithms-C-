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
    std::cout << "----------Test get_node()----------\n";
    std::cout << *tree.get_node(std::make_shared<Person>(70, "Alice09")) << std::endl;

    return 0;
}

/*
2022年4月12日 22:24:43
输出：
----------Test add()----------
height: 5
[70, Alice09] Black
[56, Alice03] Black     [87, Alice02] Black
[22, Alice06] Red       [62, Alice07] Black     [74, Alice04] Black     [96, Alice05] Black
[20, Alice08] Black     [55, Alice01] Black     [68, Alice10] Red       [90, Alice11] Red
[50, Alice12] Red

----------Test get_node()----------
[70, Alice09] Black
delete 0x786df0[70, Alice09]
delete 0x786b20[20, Alice08]
delete 0x786d60[50, Alice12]
delete 0x786730[55, Alice01]
delete 0x786a00[22, Alice06]
delete 0x786c40[68, Alice10]
delete 0x786a90[62, Alice07]
delete 0x786850[56, Alice03]
delete 0x7868e0[74, Alice04]
delete 0x786cd0[90, Alice11]
delete 0x786970[96, Alice05]
delete 0x7867c0[87, Alice02]
delete 0x786bb0[70, Alice09]
*/