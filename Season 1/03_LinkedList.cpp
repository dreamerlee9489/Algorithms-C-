#include "./03_LinkedList.h"
#include "./Person.h"
using namespace std;

int main()
{
    auto list = make_shared<LinkedList<Person>>();
    cout << "----------Test add()----------\n";
    list->add(make_shared<Person>(20, "Alice0"));
    list->add(make_shared<Person>(21, "Alice1"));
    list->add(make_shared<Person>(22, "Alice2"));
    list->add(make_shared<Person>(23, "Alice3"));
    list->add(make_shared<Person>(24, "Alice4"));
    list->add(make_shared<Person>(25, "Alice5"));
    list->add(make_shared<Person>(26, "Alice6"));
    list->add(make_shared<Person>(27, "Alice7"));
    cout << "size=" << list->size() << endl;
    cout << *list;
    cout << "----------Test insert()----------\n";
    try
    {
        list->insert(5, make_shared<Person>(30, "Bob0"));
        list->insert(15, make_shared<Person>(35, "Bob1"));
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }
    cout << "size=" << list->size() << endl;
    cout << *list;
    cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(make_shared<Person>(30, "Bob0")))
        cout << "Bob0 at index=" << list->index_of(make_shared<Person>(30, "Bob0")) << endl;

    cout << "----------Test set()----------\n";
    list->set(5, make_shared<Person>(25, "Jack"));
    cout << "size=" << list->size() << endl;
    cout << *list;
    cout << "----------Test remove()----------\n";
    try
    {
        cout << "Remove: " << *list->remove(5) << "\n";
        cout << "Remove: " << *list->remove(-1) << "\n";
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }
    cout << "size=" << list->size() << endl;
    cout << *list;
    cout << "----------Test clear()----------\n";
    list->clear();
    cout << "size=" << list->size() << endl;
    cout << "----------Test operator=(const LinkedList<T> &)----------\n";
    auto list1 = make_shared<LinkedList<Person>>();
    list1->add(make_shared<Person>(10, "test10"));
    list1->add(make_shared<Person>(11, "test11"));
    list1->add(make_shared<Person>(12, "test12"));
    auto list2 = make_shared<LinkedList<Person>>();
    list2->add(make_shared<Person>(20, "test20"));
    list2->add(make_shared<Person>(21, "test21"));
    list2->add(make_shared<Person>(22, "test22"));
    *list2 = *list1;
    cout << *list2;
    cout << "----------Test operator=(LinkedList<T> &&)----------\n";
    auto list3 = make_shared<LinkedList<Person>>();
    list3->add(make_shared<Person>(30, "test30"));
    list3->add(make_shared<Person>(31, "test31"));
    list3->add(make_shared<Person>(32, "test32"));
    *list3 = move(*list1);
    cout << *list3;
    return 0;
}

/*
2022年3月30日 15:32:00
输出:
----------Test add()----------
size=8
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test insert()----------
delete 0x6b6c00[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[30, Bob0]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test contains() & index_of()----------
delete 0x6b6d30[30, Bob0]
Bob0 at index=5
delete 0x6b6d30[30, Bob0]
----------Test set()----------
delete 0x6b6b80[30, Bob0]
size=9
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[25, Jack]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test remove()----------
Remove: [25, Jack]
delete 0x6b6d30[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test clear()----------
delete 0x6b6b00[27, Alice7]
delete 0x6b6a80[26, Alice6]
delete 0x6b6a00[25, Alice5]
delete 0x6b6980[24, Alice4]
delete 0x6b6900[23, Alice3]
delete 0x6b6880[22, Alice2]
delete 0x6b6800[21, Alice1]
delete 0x6b6780[20, Alice0]
size=0
----------Test operator=(const LinkedList<T> &)----------
delete 0x6b6880[22, test22]
delete 0x6b6800[21, test21]
delete 0x6b6780[20, test20]
[10, test10]
[11, test11]
[12, test12]
----------Test operator=(LinkedList<T> &&)----------
delete 0x6b6970[32, test32]
delete 0x6b68f0[31, test31]
delete 0x6b6870[30, test30]
[10, test10]
[11, test11]
[12, test12]
delete 0x6b6ef0[12, test12]
delete 0x6b6c50[11, test11]
delete 0x6b6c00[10, test10]
*/