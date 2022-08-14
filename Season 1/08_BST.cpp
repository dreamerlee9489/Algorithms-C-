#include "./08_BST.hpp"
#include "./Person.hpp"

using namespace app;

int main() {
    BST<Person> tree;
    tree.add(make_shared<Person>(17, "Alice17"));
    tree.add(make_shared<Person>(14, "Alice14"));
    tree.add(make_shared<Person>(12, "Alice12"));
    tree.add(make_shared<Person>(11, "Alice11"));
    tree.add(make_shared<Person>(13, "Alice13"));
    tree.add(make_shared<Person>(15, "Alice15"));
    tree.add(make_shared<Person>(19, "Alice19"));
    tree.add(make_shared<Person>(18, "Alice18"));
    tree.add(make_shared<Person>(21, "Alice21"));
    tree.add(make_shared<Person>(20, "Alice20"));
    tree.add(make_shared<Person>(22, "Alice22"));
    cout << "----------Test operator<<()----------\n";
    cout << tree;
    cout << "----------Test traverse(Level)----------\n";
    tree.traverse(BST<Person>::TraverseOrder::Level, [](shared_ptr<Person> data) {
        cout << "lambda: " << *data << "\n";
        return false;
    });
    cout << "height=" << tree.height() << "\n";
    cout << "is complete: " << tree.is_complete() << "\n";
    cout << "----------Test remove()----------\n";
    tree.remove(make_shared<Person>(17, "Alice17"));
    tree.remove(make_shared<Person>(12, "Alice12"));
    tree.remove(make_shared<Person>(19, "Alice19"));
    tree.traverse();
    cout << "----------Test clear()----------\n";
    tree.clear();
    tree.add(make_shared<Person>(17, "Alice17"));
    tree.add(make_shared<Person>(14, "Alice14"));
    tree.add(make_shared<Person>(19, "Alice19"));
    tree.add(make_shared<Person>(12, "Alice12"));
    tree.add(make_shared<Person>(15, "Alice15"));
    cout << "----------Test operator<<()----------\n";
    cout << tree;
    cout << "----------Test traverse(In)----------\n";
    tree.traverse();
    cout << "height=" << tree.height() << "\n";
    cout << "is complete: " << tree.is_complete() << "\n";
    cout << "----------Test BST(const BST<T> &)----------\n";
    BST<Person> tree2 = BST<Person>(tree);
    cout << tree2;
    cout << "----------Test BST(BST<T> &&)----------\n";
    BST<Person> tree3 = BST<Person>(move(tree));
    cout << tree3;
    cout << "----------Test traverse(Morris)----------\n";
    BST<Person> tree4;
    tree4.add(make_shared<Person>(6, "Alice6"));
    tree4.add(make_shared<Person>(2, "Alice2"));
    tree4.add(make_shared<Person>(0, "Alice0"));
    tree4.add(make_shared<Person>(4, "Alice4"));
    tree4.add(make_shared<Person>(3, "Alice3"));
    tree4.add(make_shared<Person>(5, "Alice5"));
    tree4.add(make_shared<Person>(8, "Alice8"));
    tree4.add(make_shared<Person>(7, "Alice7"));
    tree4.add(make_shared<Person>(9, "Alice9"));
    tree4.traverse(BST<Person>::TraverseOrder::Morris);

    return 0;
}

/*
----------Test operator<<()----------
[17, Alice17]
[14, Alice14]   [19, Alice19]
[12, Alice12]   [15, Alice15]   [18, Alice18]   [21, Alice21]
[11, Alice11]   [13, Alice13]   [20, Alice20]   [22, Alice22]

----------Test traverse(Level)----------
lambda: [17, Alice17]
lambda: [14, Alice14]
lambda: [19, Alice19]
lambda: [12, Alice12]
lambda: [15, Alice15]
lambda: [18, Alice18]
lambda: [21, Alice21]
lambda: [11, Alice11]
lambda: [13, Alice13]
lambda: [20, Alice20]
lambda: [22, Alice22]
height=4
is complete: 0
----------Test remove()----------
delete 0x1066730[17, Alice17]
delete 0x1066d60[17, Alice17]
delete 0x1066850[12, Alice12]
delete 0x1066730[12, Alice12]
delete 0x1066a90[19, Alice19]
delete 0x1066730[19, Alice19]
[11, Alice11]
[13, Alice13]
[14, Alice14]
[15, Alice15]
[18, Alice18]
[20, Alice20]
[21, Alice21]
[22, Alice22]
----------Test clear()----------
delete 0x10668e0[11, Alice11]
delete 0x1066970[13, Alice13]
delete 0x1066a00[15, Alice15]
delete 0x10667c0[14, Alice14]
delete 0x1066c40[20, Alice20]
delete 0x1066cd0[22, Alice22]
delete 0x1066bb0[21, Alice21]
delete 0x1066b20[18, Alice18]
----------Test operator<<()----------
[17, Alice17]
[14, Alice14]   [19, Alice19]
[12, Alice12]   [15, Alice15]

----------Test traverse(In)----------
[12, Alice12]
[14, Alice14]
[15, Alice15]
[17, Alice17]
[19, Alice19]
height=3
is complete: 1
----------Test operator=(const BST<T>&)----------
[17, Alice17]
[14, Alice14]   [19, Alice19]
[12, Alice12]   [15, Alice15]

----------Test operator=(BST<T>&&)----------
[17, Alice17]
[14, Alice14]   [19, Alice19]
[12, Alice12]   [15, Alice15]

delete 0x10668e0[12, Alice12]
delete 0x1066970[15, Alice15]
delete 0x10667c0[14, Alice14]
delete 0x1066850[19, Alice19]
delete 0x1066730[17, Alice17]
*/