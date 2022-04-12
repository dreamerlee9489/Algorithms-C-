#include "./06_AVLTree.h"
#include "./Person.h"

int main()
{
    AVLTree<Person> tree = AVLTree<Person>();
    std::cout << "----------Test add()----------\n";
    tree.add(std::make_shared<Person>(11, "Alice01"));
    tree.add(std::make_shared<Person>(12, "Alice02"));
    tree.add(std::make_shared<Person>(13, "Alice03"));
    tree.add(std::make_shared<Person>(14, "Alice04"));
    tree.add(std::make_shared<Person>(15, "Alice05"));
    tree.add(std::make_shared<Person>(16, "Alice06"));
    tree.add(std::make_shared<Person>(17, "Alice07"));
    tree.add(std::make_shared<Person>(18, "Alice08"));
    tree.add(std::make_shared<Person>(19, "Alice09"));
    tree.add(std::make_shared<Person>(20, "Alice10"));
    tree.add(std::make_shared<Person>(21, "Alice11"));
    tree.add(std::make_shared<Person>(22, "Alice12"));
    tree.add(std::make_shared<Person>(23, "Alice13"));
    tree.add(std::make_shared<Person>(24, "Alice14"));
    tree.add(std::make_shared<Person>(25, "Alice15"));
    tree.add(std::make_shared<Person>(26, "Alice16"));
    std::cout << "height: " << tree.height() << "\n";
    std::cout << tree;
    std::cout << "----------Test remove()----------\n";
    tree.remove(std::make_shared<Person>(21, "Alice11"));
    tree.remove(std::make_shared<Person>(20, "Alice10"));
    std::cout << "height: " << tree.height() << "\n";
    std::cout << tree;
    std::cout << "----------Test get_node()----------\n";
    std::cout << *tree.get_node(std::make_shared<Person>(17, "Alice07")) << std::endl;

    return 0;
}

/*
2022年4月11日 20:24:12
----------Test add()----------
height: 5
[18, Alice08] h:5
[14, Alice04] h:3       [22, Alice12] h:4
[12, Alice02] h:2       [16, Alice06] h:2       [20, Alice10] h:2       [24, Alice14] h:3
[11, Alice01] h:1       [13, Alice03] h:1       [15, Alice05] h:1       [17, Alice07] h:1       [19, Alice09] h:1       [21, Alice11] h:1       [23, Alice13] h:1       [25, Alice15] h:2
[26, Alice16] h:1

----------Test remove()----------
delete 0x696cd0[21, Alice11]
delete 0x6971d0[21, Alice11]
delete 0x696c40[20, Alice10]
delete 0x697040[20, Alice10]
height: 4
[18, Alice08] h:4
[14, Alice04] h:3       [24, Alice14] h:3
[12, Alice02] h:2       [16, Alice06] h:2       [22, Alice12] h:2       [25, Alice15] h:2
[11, Alice01] h:1       [13, Alice03] h:1       [15, Alice05] h:1       [17, Alice07] h:1       [19, Alice09] h:1       [23, Alice13] h:1       [26, Alice16] h:1

----------Test get_node()----------
[17, Alice07] h:1
delete 0x6975e0[17, Alice07]
delete 0x696730[11, Alice01]
delete 0x696850[13, Alice03]
delete 0x6967c0[12, Alice02]
delete 0x696970[15, Alice05]
delete 0x696a90[17, Alice07]
delete 0x696a00[16, Alice06]
delete 0x6968e0[14, Alice04]
delete 0x696bb0[19, Alice09]
delete 0x696df0[23, Alice13]
delete 0x696d60[22, Alice12]
delete 0x6b1ca0[26, Alice16]
delete 0x696f10[25, Alice15]
delete 0x696e80[24, Alice14]
delete 0x696b20[18, Alice08]
*/