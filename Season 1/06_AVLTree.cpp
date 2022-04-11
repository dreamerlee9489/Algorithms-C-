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

    return 0;
}

/*
2022年4月11日 20:24:12
----------Test add()----------
height: 5
[18, Alice08]
[14, Alice04]   [22, Alice12]
[12, Alice02]   [16, Alice06]   [20, Alice10]   [24, Alice14]
[11, Alice01]   [13, Alice03]   [15, Alice05]   [17, Alice07]   [19, Alice09]   [21, Alice11]   [23, Alice13]   [25, Alice15]
[26, Alice16]

----------Test remove()----------
delete 0xe66c00[21, Alice11]
delete 0xe676a0[21, Alice11]
delete 0xe66b70[20, Alice10]
delete 0xe670b0[20, Alice10]
height: 4
[18, Alice08]
[14, Alice04]   [24, Alice14]
[12, Alice02]   [16, Alice06]   [22, Alice12]   [25, Alice15]
[11, Alice01]   [13, Alice03]   [15, Alice05]   [17, Alice07]   [19, Alice09]   [23, Alice13]   [26, Alice16]

delete 0xe66660[11, Alice01]
delete 0xe66780[13, Alice03]
delete 0xe666f0[12, Alice02]
delete 0xe668a0[15, Alice05]
delete 0xe669c0[17, Alice07]
delete 0xe66930[16, Alice06]
delete 0xe66810[14, Alice04]
delete 0xe66ae0[19, Alice09]
delete 0xe66d20[23, Alice13]
delete 0xe66c90[22, Alice12]
delete 0xe66ed0[26, Alice16]
delete 0xe66e40[25, Alice15]
delete 0xe66db0[24, Alice14]
delete 0xe66a50[18, Alice08]
*/