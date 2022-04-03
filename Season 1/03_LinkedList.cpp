#include "./03_LinkedList.h"
#include "./Person.h"

int main()
{
    auto list = std::make_shared<LinkedList<Person>>();
    std::cout << "----------Test add()----------\n";
    std::cout << "Add: " << *list->add(std::make_shared<Person>(20, "Alice0"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(21, "Alice1"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(22, "Alice2"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(23, "Alice3"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(24, "Alice4"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(25, "Alice5"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(26, "Alice6"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(27, "Alice7"));
    std::cout << "size=" << list->size() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test insert()----------\n";
    try
    {
        std::cout << "Insert: " << *list->insert(5, std::make_shared<Person>(30, "Bob0"));
        std::cout << "Insert: " << *list->insert(15, std::make_shared<Person>(35, "Bob1"));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "size=" << list->size() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(std::make_shared<Person>(30, "Bob0")))
        std::cout << "Bob0 at index=" << list->index_of(std::make_shared<Person>(30, "Bob0")) << std::endl;

    std::cout << "----------Test set()----------\n";
    std::cout << "Set: " << *list->set(5, std::make_shared<Person>(25, "Jack"));
    std::cout << "size=" << list->size() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test remove()----------\n";
    try
    {
        std::cout << "Remove: " << *list->remove(5);
        std::cout << "Remove: " << *list->remove(-1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "size=" << list->size() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test clear()----------\n";
    list->clear();
    std::cout << "size=" << list->size() << std::endl;

    std::cout << "----------Test LinkedList(const LinkedList<T> &)----------\n";
    auto list1 = std::make_shared<LinkedList<Person>>();
    list1->add(std::make_shared<Person>(10, "test0"));
    list1->add(std::make_shared<Person>(11, "test1"));
    list1->add(std::make_shared<Person>(12, "test2"));
    auto list2 = std::make_shared<LinkedList<Person>>(*list1);
    for (size_t i = 0; i < list2->size(); ++i)
        std::cout << *list2->get(i);

    std::cout << "----------Test LinkedList(LinkedList<T> &&)----------\n";
    auto list3 = std::make_shared<LinkedList<Person>>(std::move(*list1));
    for (size_t i = 0; i < list3->size(); ++i)
        std::cout << *list3->get(i);
    std::getchar();
    return 0;
}

/*
2022年3月30日 15:32:00
输出:
----------Test add()----------
Add: 0x6f6750[20, Alice0]
Add: 0x6f67c0[21, Alice1]
Add: 0x6f6830[22, Alice2]
Add: 0x6f68a0[23, Alice3]
Add: 0x6f6910[24, Alice4]
Add: 0x6f6980[25, Alice5]
Add: 0x6f69f0[26, Alice6]
Add: 0x6f6a60[27, Alice7]
size=8
0x6f6750[20, Alice0]
0x6f67c0[21, Alice1]
0x6f6830[22, Alice2]
0x6f68a0[23, Alice3]
0x6f6910[24, Alice4]
0x6f6980[25, Alice5]
0x6f69f0[26, Alice6]
0x6f6a60[27, Alice7]
----------Test insert()----------
Insert: 0x6f6ad0[30, Bob0]
Insert: delete 0x6f6b40[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9
0x6f6750[20, Alice0]
0x6f67c0[21, Alice1]
0x6f6830[22, Alice2]
0x6f68a0[23, Alice3]
0x6f6910[24, Alice4]
0x6f6ad0[30, Bob0]
0x6f6980[25, Alice5]
0x6f69f0[26, Alice6]
0x6f6a60[27, Alice7]
----------Test contains() & index_of()----------
delete 0x6f6c60[30, Bob0]
Bob0 at index=5
delete 0x6f6c60[30, Bob0]
----------Test set()----------
Set: delete 0x6f6ad0[30, Bob0]
0x6f6c60[25, Jack]
size=9
0x6f6750[20, Alice0]
0x6f67c0[21, Alice1]
0x6f6830[22, Alice2]
0x6f68a0[23, Alice3]
0x6f6910[24, Alice4]
0x6f6c60[25, Jack]
0x6f6980[25, Alice5]
0x6f69f0[26, Alice6]
0x6f6a60[27, Alice7]
----------Test remove()----------
Remove: 0x6f6c60[25, Jack]
delete 0x6f6c60[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8
0x6f6750[20, Alice0]
0x6f67c0[21, Alice1]
0x6f6830[22, Alice2]
0x6f68a0[23, Alice3]
0x6f6910[24, Alice4]
0x6f6980[25, Alice5]
0x6f69f0[26, Alice6]
0x6f6a60[27, Alice7]
----------Test clear()----------
delete 0x6f6a60[27, Alice7]
delete 0x6f69f0[26, Alice6]
delete 0x6f6980[25, Alice5]
delete 0x6f6910[24, Alice4]
delete 0x6f68a0[23, Alice3]
delete 0x6f6830[22, Alice2]
delete 0x6f67c0[21, Alice1]
delete 0x6f6750[20, Alice0]
size=0
----------Test LinkedList(const LinkedList<T> &)----------
0x6f6cc0[10, test0]
0x6f6b70[11, test1]
0x6f6be0[12, test2]
----------Test LinkedList(LinkedList<T> &&)----------
0x6f6cc0[10, test0]
0x6f6b70[11, test1]
0x6f6be0[12, test2]

delete 0x6f6be0[12, test2]
delete 0x6f6b70[11, test1]
delete 0x6f6cc0[10, test0]
*/