#include "./10_RBTree.h"
#include "./Person.h"
using namespace std;

int main()
{
    RBTree<Person> tree;
    cout << "----------Test add()----------\n";
    tree.add(make_shared<Person>(55, "Alice01"));
    tree.add(make_shared<Person>(87, "Alice02"));
    tree.add(make_shared<Person>(56, "Alice03"));
    tree.add(make_shared<Person>(74, "Alice04"));
    tree.add(make_shared<Person>(96, "Alice05"));
    tree.add(make_shared<Person>(22, "Alice06"));
    tree.add(make_shared<Person>(62, "Alice07"));
    tree.add(make_shared<Person>(20, "Alice08"));
    tree.add(make_shared<Person>(70, "Alice09"));
    tree.add(make_shared<Person>(68, "Alice10"));
    tree.add(make_shared<Person>(90, "Alice11"));
    tree.add(make_shared<Person>(50, "Alice12"));
    cout << "height: " << tree.height() << "\n";
    cout << tree;
    cout << "----------Test remove()----------\n";
    tree.remove(make_shared<Person>(55, "Alice01"));
    tree.remove(make_shared<Person>(87, "Alice02"));
    tree.remove(make_shared<Person>(56, "Alice03"));
    cout << "height: " << tree.height() << "\n";
    cout << tree;
    cout << "----------Test RBTree(const RBTree<T> &)----------\n";
    RBTree<Person> tree2 = RBTree<Person>(tree);
    cout << tree2;
    cout << "----------Test RBTree(RBTree<T> &&)----------\n";
    RBTree<Person> tree3 = RBTree<Person>(move(tree));
    cout << tree3;
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
delete 0x7b6660[55, Alice01]
delete 0x7b6d20[55, Alice01]
delete 0x7b66f0[87, Alice02]
delete 0x7b6660[87, Alice02]
delete 0x7b6780[56, Alice03]
delete 0x7b6660[56, Alice03]
height: 4
[70, Alice09] BLACK
[62, Alice07] BLACK     [90, Alice11] BLACK
[22, Alice06] R E D     [68, Alice10] BLACK     [74, Alice04] BLACK     [96, Alice05] BLACK
[20, Alice08] BLACK     [50, Alice12] BLACK

----------Test RBTree(const RBTree<T> &)----------
[70, Alice09] BLACK
[62, Alice07] R E D     [90, Alice11] BLACK
[22, Alice06] BLACK     [68, Alice10] BLACK     [74, Alice04] R E D     [96, Alice05] R E D
[20, Alice08] R E D     [50, Alice12] R E D

----------Test RBTree(RBTree<T> &&)----------
[70, Alice09] BLACK
[62, Alice07] BLACK     [90, Alice11] BLACK
[22, Alice06] R E D     [68, Alice10] BLACK     [74, Alice04] BLACK     [96, Alice05] BLACK
[20, Alice08] BLACK     [50, Alice12] BLACK

delete 0x7b6a50[20, Alice08]
delete 0x7b6c90[50, Alice12]
delete 0x7b6930[22, Alice06]
delete 0x7b6b70[68, Alice10]
delete 0x7b69c0[62, Alice07]
delete 0x7b6810[74, Alice04]
delete 0x7b68a0[96, Alice05]
delete 0x7b6c00[90, Alice11]
delete 0x7b6ae0[70, Alice09]
*/