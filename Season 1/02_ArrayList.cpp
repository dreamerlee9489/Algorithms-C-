#include "./02_ArrayList.h"
#include "./Person.h"

int main()
{
    auto list = std::make_shared<ArrayList<Person>>();
    std::cout << "----------Test add()----------\n";
    std::cout << "Add: " << *list->add(std::make_shared<Person>(20, "Alice0"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(21, "Alice1"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(22, "Alice2"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(23, "Alice3"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(24, "Alice4"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(25, "Alice5"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(26, "Alice6"));
    std::cout << "Add: " << *list->add(std::make_shared<Person>(27, "Alice7"));
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
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
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(std::make_shared<Person>(30, "Bob0")))
        std::cout << "Bob0 at index=" << list->index_of(std::make_shared<Person>(30, "Bob0")) << std::endl;

    std::cout << "----------Test set()----------\n";
    std::cout << "Set: " << *list->set(5, std::make_shared<Person>(25, "Jack"));
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
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
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;
    for (size_t i = 0; i < list->size(); ++i)
        std::cout << *list->get(i);

    std::cout << "----------Test clear()----------\n";
    list->clear();
    std::cout << "size=" << list->size() << ", capacity=" << list->capacity() << std::endl;

    std::cout << "----------Test operator=(const ArrayList<T> &)----------\n";
    auto list1 = std::make_shared<ArrayList<Person>>();
    list1->add(std::make_shared<Person>(10, "test10"));
    list1->add(std::make_shared<Person>(11, "test11"));
    list1->add(std::make_shared<Person>(12, "test12"));
    auto list2 = std::make_shared<ArrayList<Person>>();
    list2->add(std::make_shared<Person>(20, "test20"));
    list2->add(std::make_shared<Person>(21, "test21"));
    list2->add(std::make_shared<Person>(22, "test22"));
    *list2 = *list1;
    for (size_t i = 0; i < list2->size(); ++i)
        std::cout << *list2->get(i);

    std::cout << "----------Test operator=(ArrayList<T> &&)----------\n";
    auto list3 = std::make_shared<ArrayList<Person>>();
    list3->add(std::make_shared<Person>(30, "test30"));
    list3->add(std::make_shared<Person>(31, "test31"));
    list3->add(std::make_shared<Person>(32, "test32"));
    *list3 = std::move(*list1);
    for (size_t i = 0; i < list3->size(); ++i)
        std::cout << *list3->get(i);
    std::getchar();
    return 0;
}

/*
2022年3月30日 16:12:20
输出:
----------Test add()----------
Add: 0x2602120[20, Alice0]
Add: 0x26021a0[21, Alice1]
Add: 0x2602220[22, Alice2]
Add: 0x26022a0[23, Alice3]
Add: 0x2602320[24, Alice4]
Add: 0x26023a0[25, Alice5]
Add: 0x2602420[26, Alice6]
Add: 0x26024a0[27, Alice7]
size=8, capacity=8
0x2602120[20, Alice0]
0x26021a0[21, Alice1]
0x2602220[22, Alice2]
0x26022a0[23, Alice3]
0x2602320[24, Alice4]
0x26023a0[25, Alice5]
0x2602420[26, Alice6]
0x26024a0[27, Alice7]
----------Test insert()----------
Insert: 0x2602520[30, Bob0]
Insert: delete 0x26026f0[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9, capacity=16
0x2602120[20, Alice0]
0x26021a0[21, Alice1]
0x2602220[22, Alice2]
0x26022a0[23, Alice3]
0x2602320[24, Alice4]
0x2602520[30, Bob0]
0x26023a0[25, Alice5]
0x2602420[26, Alice6]
0x26024a0[27, Alice7]
----------Test contains() & index_of()----------
delete 0x2602ca0[30, Bob0]
Bob0 at index=5
delete 0x2602d20[30, Bob0]
----------Test set()----------
Set: delete 0x2602520[30, Bob0]
0x2602da0[25, Jack]
size=9, capacity=16
0x2602120[20, Alice0]
0x26021a0[21, Alice1]
0x2602220[22, Alice2]
0x26022a0[23, Alice3]
0x2602320[24, Alice4]
0x2602da0[25, Jack]
0x26023a0[25, Alice5]
0x2602420[26, Alice6]
0x26024a0[27, Alice7]
----------Test remove()----------
Remove: 0x2602da0[25, Jack]
delete 0x2602da0[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8, capacity=16
0x2602120[20, Alice0]
0x26021a0[21, Alice1]
0x2602220[22, Alice2]
0x26022a0[23, Alice3]
0x2602320[24, Alice4]
0x26023a0[25, Alice5]
0x2602420[26, Alice6]
0x26024a0[27, Alice7]
----------Test clear()----------
delete 0x26024a0[27, Alice7]
delete 0x2602420[26, Alice6]
delete 0x26023a0[25, Alice5]
delete 0x2602320[24, Alice4]
delete 0x26022a0[23, Alice3]
delete 0x2602220[22, Alice2]
delete 0x26021a0[21, Alice1]
delete 0x2602120[20, Alice0]
size=0, capacity=16
----------Test operator=(const ArrayList<T> &)----------
delete 0x9d8380[22, test22]
delete 0x9d8580[21, test21]
delete 0x9d8700[20, test20]
0x9d7e00[10, test10]
0x9d8000[11, test11]
0x9d7f80[12, test12]
----------Test operator=(ArrayList<T> &&)----------
delete 0x9d8780[32, test32]
delete 0x9d8080[31, test31]
delete 0x9d8600[30, test30]
0x9d7e00[10, test10]
0x9d8000[11, test11]
0x9d7f80[12, test12]

delete 0x9d7f80[12, test12]
delete 0x9d8000[11, test11]
delete 0x9d7e00[10, test10]
*/