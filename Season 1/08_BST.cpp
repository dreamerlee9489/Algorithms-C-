#include "./08_BST.h"
#include "./Person.h"

int main()
{
    BST<Person> tree = BST<Person>();
    tree.add(std::make_shared<Person>(17, "Alice17"));
    tree.add(std::make_shared<Person>(14, "Alice14"));
    tree.add(std::make_shared<Person>(12, "Alice12"));
    tree.add(std::make_shared<Person>(11, "Alice11"));
    tree.add(std::make_shared<Person>(13, "Alice13"));
    tree.add(std::make_shared<Person>(15, "Alice15"));
    tree.add(std::make_shared<Person>(19, "Alice19"));
    tree.add(std::make_shared<Person>(18, "Alice18"));
    tree.add(std::make_shared<Person>(21, "Alice21"));
    tree.add(std::make_shared<Person>(20, "Alice20"));
    tree.add(std::make_shared<Person>(22, "Alice22"));
    std::cout << "----------Test operator<<()----------\n";
    std::cout << tree;
    std::cout << "----------Test traverse(Level)----------\n";
    tree.traverse(BST<Person>::TraverseOrder::Level, [](std::shared_ptr<Person> data)
                  { std::cout << "lambda: " << *data << "\n"; });
    std::cout << "height=" << tree.height() << "\n";
    std::cout << "is complete: " << tree.is_complete() << "\n";
    std::cout << "----------Test remove()----------\n";
    tree.remove(std::make_shared<Person>(17, "Alice17"));
    tree.remove(std::make_shared<Person>(12, "Alice12"));
    tree.remove(std::make_shared<Person>(19, "Alice19"));
    tree.traverse();
    std::cout << "----------Test clear()----------\n";
    tree.clear();
    tree.add(std::make_shared<Person>(17, "Alice17"));
    tree.add(std::make_shared<Person>(14, "Alice14"));
    tree.add(std::make_shared<Person>(19, "Alice19"));
    tree.add(std::make_shared<Person>(12, "Alice12"));
    tree.add(std::make_shared<Person>(15, "Alice15"));
    std::cout << "----------Test operator<<()----------\n";
    std::cout << tree;
    std::cout << "----------Test traverse(In)----------\n";
    tree.traverse();
    std::cout << "height=" << tree.height() << "\n";
    std::cout << "is complete: " << tree.is_complete() << "\n";
    std::cout << "----------Test BST(const BST<T> &)----------\n";
    BST<Person> tree2 = BST<Person>(tree);
    std::cout << tree2;
    std::cout << "----------Test BST(BST<T> &&)----------\n";
    BST<Person> tree3 = BST<Person>(std::move(tree));
    std::cout << tree3;
    return 0;
}

/*
2022年4月9日 12:01:06
输出：
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