#include "./02_ArrayList.h"
#include "./Person.h"
using namespace std;

int main()
{
    auto list = make_shared<ArrayList<Person>>();
    cout << "----------Test add()----------\n";
    list->add(make_shared<Person>(20, "Alice0"));
    list->add(make_shared<Person>(21, "Alice1"));
    list->add(make_shared<Person>(22, "Alice2"));
    list->add(make_shared<Person>(23, "Alice3"));
    list->add(make_shared<Person>(24, "Alice4"));
    list->add(make_shared<Person>(25, "Alice5"));
    list->add(make_shared<Person>(26, "Alice6"));
    list->add(make_shared<Person>(27, "Alice7"));
    cout << "size=" << list->size() << ", capacity=" << list->capacity() << endl;
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
    cout << "size=" << list->size() << ", capacity=" << list->capacity() << endl;
    cout << *list;
    cout << "----------Test contains() & index_of()----------\n";
    if (list->contains(make_shared<Person>(30, "Bob0")))
        cout << "Bob0 at index=" << list->index_of(make_shared<Person>(30, "Bob0")) << endl;

    cout << "----------Test set()----------\n";
    list->set(5, make_shared<Person>(25, "Jack"));
    cout << "size=" << list->size() << ", capacity=" << list->capacity() << endl;
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
    cout << "size=" << list->size() << ", capacity=" << list->capacity() << endl;
    cout << *list;
    cout << "----------Test clear()----------\n";
    list->clear();
    cout << "size=" << list->size() << ", capacity=" << list->capacity() << endl;
    cout << "----------Test operator=(const ArrayList<T> &)----------\n";
    auto list1 = make_shared<ArrayList<Person>>();
    list1->add(make_shared<Person>(10, "test10"));
    list1->add(make_shared<Person>(11, "test11"));
    list1->add(make_shared<Person>(12, "test12"));
    auto list2 = make_shared<ArrayList<Person>>();
    list2->add(make_shared<Person>(20, "test20"));
    list2->add(make_shared<Person>(21, "test21"));
    list2->add(make_shared<Person>(22, "test22"));
    *list2 = *list1;
    cout << *list2;
    cout << "----------Test operator=(ArrayList<T> &&)----------\n";
    auto list3 = make_shared<ArrayList<Person>>();
    list3->add(make_shared<Person>(30, "test30"));
    list3->add(make_shared<Person>(31, "test31"));
    list3->add(make_shared<Person>(32, "test32"));
    *list3 = move(*list1);
    cout << *list3;
    return 0;
}

/*
2022年3月30日 16:12:20
输出:
----------Test add()----------
size=8, capacity=8
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test insert()----------
delete 0xdd6bd0[35, Bob1]
index = 15 out of range for add: [0, 9].
size=9, capacity=16
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
delete 0xdd6d00[30, Bob0]
Bob0 at index=5
delete 0xdd6d00[30, Bob0]
----------Test set()----------
delete 0xdd6a70[30, Bob0]
size=9, capacity=16
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
delete 0xdd6d00[25, Jack]
Remove: index = -1 out of range: [0, 7].
size=8, capacity=16
[20, Alice0]
[21, Alice1]
[22, Alice2]
[23, Alice3]
[24, Alice4]
[25, Alice5]
[26, Alice6]
[27, Alice7]
----------Test clear()----------
size=0, capacity=16
----------Test operator=(const ArrayList<T> &)----------
delete 0xdd6f90[20, test20]
delete 0x2591ca0[21, test21]
delete 0x2591cf0[22, test22]
[10, test10]
[11, test11]
[12, test12]
----------Test operator=(ArrayList<T> &&)----------
delete 0x2591d30[30, test30]
delete 0x2591d80[31, test31]
delete 0x2591dd0[32, test32]
[10, test10]
[11, test11]
[12, test12]
delete 0xdd6bd0[10, test10]
delete 0xdd6c20[11, test11]
delete 0xdd6c70[12, test12]
*/