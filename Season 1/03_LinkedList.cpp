#include "./03_LinkedList.h"
#include "./Person.h"

int main()
{
    auto list = std::make_shared<LinkedList<Person>>();
    std::cout << "----------Test add()----------\n";
    list->add(std::make_shared<Person>(20, "Alice0"));
    list->add(std::make_shared<Person>(21, "Alice1"));
    list->add(std::make_shared<Person>(22, "Alice2"));
    list->add(std::make_shared<Person>(23, "Alice3"));
    list->add(std::make_shared<Person>(24, "Alice4"));
    list->add(std::make_shared<Person>(25, "Alice5"));
    list->add(std::make_shared<Person>(26, "Alice6"));
    list->add(std::make_shared<Person>(27, "Alice7"));
    std::cout << "size=" << list->size() << std::endl;
    std::cout << *list;
    std::cout << "----------Test insert()----------\n";
    try
    {
        list->insert(5, std::make_shared<Person>(30, "Bob0"));
        list->insert(15, std::make_shared<Person>(35, "Bob1"));
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "size=" << list->size() << std::endl;
    std::cout << *list;
    std::cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(std::make_shared<Person>(30, "Bob0")))
        std::cout << "Bob0 at index=" << list->index_of(std::make_shared<Person>(30, "Bob0")) << std::endl;

    std::cout << "----------Test set()----------\n";
    list->set(5, std::make_shared<Person>(25, "Jack"));
    std::cout << "size=" << list->size() << std::endl;
    std::cout << *list;
    std::cout << "----------Test remove()----------\n";
    try
    {
        std::cout << "Remove: " << *list->remove(5) << "\n";
        std::cout << "Remove: " << *list->remove(-1) << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    std::cout << "size=" << list->size() << std::endl;
    std::cout << *list;
    std::cout << "----------Test clear()----------\n";
    list->clear();
    std::cout << "size=" << list->size() << std::endl;
    std::cout << "----------Test operator=(const LinkedList<T> &)----------\n";
    auto list1 = std::make_shared<LinkedList<Person>>();
    list1->add(std::make_shared<Person>(10, "test10"));
    list1->add(std::make_shared<Person>(11, "test11"));
    list1->add(std::make_shared<Person>(12, "test12"));
    auto list2 = std::make_shared<LinkedList<Person>>();
    list2->add(std::make_shared<Person>(20, "test20"));
    list2->add(std::make_shared<Person>(21, "test21"));
    list2->add(std::make_shared<Person>(22, "test22"));
    *list2 = *list1;
    std::cout << *list2;
    std::cout << "----------Test operator=(LinkedList<T> &&)----------\n";
    auto list3 = std::make_shared<LinkedList<Person>>();
    list3->add(std::make_shared<Person>(30, "test30"));
    list3->add(std::make_shared<Person>(31, "test31"));
    list3->add(std::make_shared<Person>(32, "test32"));
    *list3 = std::move(*list1);
    std::cout << *list3;
    return 0;
}

/*
2022年3月30日 15:32:00
输出:
----------Test add()----------
Add: 0x8f20a0[20, Alice0]
Add: 0x8f2180[21, Alice1]
Add: 0x8f2260[22, Alice2]
Add: 0x8f2340[23, Alice3]
Add: 0xaa6fa0[24, Alice4]
Add: 0xaa7020[25, Alice5]
Add: 0xaa70a0[26, Alice6]
Add: 0xaa7120[27, Alice7]
size=8
0x8f20a0[20, Alice0]
0x8f2180[21, Alice1]
0x8f2260[22, Alice2]
0x8f2340[23, Alice3]
0xaa6fa0[24, Alice4]
0xaa7020[25, Alice5]
0xaa70a0[26, Alice6]
0xaa7120[27, Alice7]
----------Test insert()----------
Insert: 0xaa71a0[30, Bob0]
Insert: delete 0xaa7220[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9
0x8f20a0[20, Alice0]
0x8f2180[21, Alice1]
0x8f2260[22, Alice2]
0x8f2340[23, Alice3]
0xaa6fa0[24, Alice4]
0xaa71a0[30, Bob0]
0xaa7020[25, Alice5]
0xaa70a0[26, Alice6]
0xaa7120[27, Alice7]
----------Test contains() & index_of()----------
delete 0xaa7650[30, Bob0]
Bob0 at index=5
delete 0xaa76d0[30, Bob0]
----------Test set()----------
Set: delete 0xaa71a0[30, Bob0]
0xaa7750[25, Jack]
size=9
0x8f20a0[20, Alice0]
0x8f2180[21, Alice1]
0x8f2260[22, Alice2]
0x8f2340[23, Alice3]
0xaa6fa0[24, Alice4]
0xaa7750[25, Jack]
0xaa7020[25, Alice5]
0xaa70a0[26, Alice6]
0xaa7120[27, Alice7]
----------Test remove()----------
Remove: 0xaa7750[25, Jack]
delete 0xaa7750[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8
0x8f20a0[20, Alice0]
0x8f2180[21, Alice1]
0x8f2260[22, Alice2]
0x8f2340[23, Alice3]
0xaa6fa0[24, Alice4]
0xaa7020[25, Alice5]
0xaa70a0[26, Alice6]
0xaa7120[27, Alice7]
----------Test clear()----------
delete 0xaa7120[27, Alice7]
delete 0xaa70a0[26, Alice6]
delete 0xaa7020[25, Alice5]
delete 0xaa6fa0[24, Alice4]
delete 0x8f2340[23, Alice3]
delete 0x8f2260[22, Alice2]
delete 0x8f2180[21, Alice1]
delete 0x8f20a0[20, Alice0]
size=0
----------Test operator=(const LinkedList<T> &)----------
delete 0xaa80e0[22, test22]
delete 0xaa84e0[21, test21]
delete 0xaa83e0[20, test20]
0xaa7a10[10, test10]
0xaa87e0[11, test11]
0xaa8460[12, test12]
----------Test operator=(LinkedList<T> &&)----------
delete 0xaa88e0[32, test32]
delete 0xaa8560[31, test31]
delete 0xaa7b60[30, test30]
0xaa7a10[10, test10]
0xaa87e0[11, test11]
0xaa8460[12, test12]

delete 0xaa8460[12, test12]
delete 0xaa87e0[11, test11]
delete 0xaa7a10[10, test10]
*/