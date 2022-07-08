#include "./17_BinaryHeap.hpp"
#include "./Person.hpp"
using namespace app;

void test1();
void test2();
/**
 * @brief 找出数组中最大的前k个数
 * @param array
 * @param k
 */
void top_k(int array[], size_t k);

int main(int argc, char const *argv[])
{
    // test1();
    // test2();
    int array[] = {36, 15, 74, 44, 98, 99, 71, 12, 94, 32, 80, 22, 79, 38, 17, 6, 1, 28, 84, 73, 96, 62, 16, 24, 34};
    top_k(array, 5);
    return 0;
}

void test1()
{
    BinaryHeap<Person> heap;
    heap.add(make_shared<Person>(88));
    heap.add(make_shared<Person>(44));
    heap.add(make_shared<Person>(53));
    heap.add(make_shared<Person>(41));
    heap.add(make_shared<Person>(16));
    heap.add(make_shared<Person>(6));
    heap.add(make_shared<Person>(70));
    heap.add(make_shared<Person>(18));
    heap.add(make_shared<Person>(85));
    heap.add(make_shared<Person>(98));
    heap.add(make_shared<Person>(81));
    heap.add(make_shared<Person>(23));
    heap.add(make_shared<Person>(36));
    heap.add(make_shared<Person>(43));
    heap.add(make_shared<Person>(37));
    cout << "size=" << heap.size() << ", capacity=" << heap.capacity() << "\n";
    heap.traverse();
    heap.replace(make_shared<Person>(75));
    cout << "size=" << heap.size() << ", capacity=" << heap.capacity() << "\n";
    heap.traverse();
    heap.remove();
    heap.remove();
    cout << "size=" << heap.size() << ", capacity=" << heap.capacity() << "\n";
    heap.traverse();
}

void test2()
{
    shared_ptr<Person> *array = new shared_ptr<Person>[15]
    {
        make_shared<Person>(88),
        make_shared<Person>(44),
        make_shared<Person>(53),
        make_shared<Person>(41),
        make_shared<Person>(16),
        make_shared<Person>(6),
        make_shared<Person>(70),
        make_shared<Person>(18),
        make_shared<Person>(85),
        make_shared<Person>(98),
        make_shared<Person>(81),
        make_shared<Person>(23),
        make_shared<Person>(36),
        make_shared<Person>(43),
        make_shared<Person>(37)
    };
    BinaryHeap<Person> heap = BinaryHeap<Person>([](shared_ptr<Person> a, shared_ptr<Person> b)
                                                 { return (*b)._age - (*a)._age; },
                                                 array, 15);
    cout << "size=" << heap.size() << ", capacity=" << heap.capacity() << "\n";
    heap.traverse();
    delete[] array;
}

void top_k(int array[], size_t k)
{
    BinaryHeap<int> heap = BinaryHeap<int>([](shared_ptr<int> a, shared_ptr<int> b)
                                           { return *b - *a; });
    for (size_t i = 0; i < 25; ++i)
    {
        if (heap.size() < k)
            heap.add(make_shared<int>(array[i]));
        else if (array[i] > *heap.get())
            heap.replace(make_shared<int>(array[i]));
    }
    heap.traverse();
}

/*
test1():
size=15, capacity=16
[98, unnamed]
[88, unnamed]   [70, unnamed]
[44, unnamed]   [85, unnamed]   [36, unnamed]   [53, unnamed]
[18, unnamed]   [41, unnamed]   [16, unnamed]   [81, unnamed]   [6, unnamed]    [23, unnamed]   [43, unnamed]   [37, unnamed]
delete 0xdf66c0[98, unnamed]
size=15, capacity=16
[88, unnamed]
[85, unnamed]   [70, unnamed]
[44, unnamed]   [81, unnamed]   [36, unnamed]   [53, unnamed]
[18, unnamed]   [41, unnamed]   [16, unnamed]   [75, unnamed]   [6, unnamed]    [23, unnamed]   [43, unnamed]   [37, unnamed]
delete 0xdf6750[88, unnamed]
delete 0xdf6a50[85, unnamed]
size=13, capacity=16
[81, unnamed]
[75, unnamed]   [70, unnamed]
[44, unnamed]   [43, unnamed]   [36, unnamed]   [53, unnamed]
[18, unnamed]   [41, unnamed]   [16, unnamed]   [37, unnamed]   [6, unnamed]    [23, unnamed]
delete 0xdf6c20[23, unnamed]
delete 0xdf6930[6, unnamed]
delete 0xdf6d40[37, unnamed]
delete 0xdf68d0[16, unnamed]
delete 0xdf6870[41, unnamed]
delete 0xdf69f0[18, unnamed]
delete 0xdf6810[53, unnamed]
delete 0xdf6c80[36, unnamed]
delete 0xdf6ce0[43, unnamed]
delete 0xdf67b0[44, unnamed]
delete 0xdf6990[70, unnamed]
delete 0xdf6da0[75, unnamed]
delete 0xdf6bc0[81, unnamed]
test2():
size=15, capacity=15
[6, unnamed]
[16, unnamed]   [23, unnamed]
[18, unnamed]   [44, unnamed]   [36, unnamed]   [37, unnamed]
[41, unnamed]   [85, unnamed]   [98, unnamed]   [81, unnamed]   [53, unnamed]   [88, unnamed]   [43, unnamed]   [70, unnamed]
delete 0x1006a00[70, unnamed]
delete 0x1006ca0[43, unnamed]
delete 0x10067c0[88, unnamed]
delete 0x1006880[53, unnamed]
delete 0x1006b80[81, unnamed]
delete 0x1006b20[98, unnamed]
delete 0x1006ac0[85, unnamed]
delete 0x10068e0[41, unnamed]
delete 0x1006d00[37, unnamed]
delete 0x1006c40[36, unnamed]
delete 0x1006820[44, unnamed]
delete 0x1006a60[18, unnamed]
delete 0x1006be0[23, unnamed]
delete 0x1006940[16, unnamed]
delete 0x10069a0[6, unnamed]
top_k():
84
94      96
99      98
*/