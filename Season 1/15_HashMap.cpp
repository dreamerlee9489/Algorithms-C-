#include "./15_HashMap.h"
#include "./Person.h"
using namespace std;

int main(int argc, char const *argv[])
{
    HashMap<Person, int> map;
    map.add(make_shared<Person>(10, "Alice10"), make_shared<int>(10));
    map.add(make_shared<Person>(11, "Alice11"), make_shared<int>(11));
    map.add(make_shared<Person>(12, "Alice12"), make_shared<int>(12));
    map.add(make_shared<Person>(13, "Alice13"), make_shared<int>(13));
    map.add(make_shared<Person>(14, "Alice14"), make_shared<int>(14));
    cout << "size=" << map.size() << ", capacity=" << map.capacity() << "\n";
    map.traverse();
    map.remove(make_shared<Person>(11, "Alice11"));
    map.remove(make_shared<Person>(13, "Alice13"));
    cout << "size=" << map.size() << ", capacity=" << map.capacity() << "\n";
    map.traverse();
    map.add(make_shared<Person>(10, "Alice10"), make_shared<int>(30));
    map.add(make_shared<Person>(12, "Alice12"), make_shared<int>(36));
    map.add(make_shared<Person>(14, "Alice14"), make_shared<int>(42));
    cout << "size=" << map.size() << ", capacity=" << map.capacity() << "\n";
    map.traverse();
    for (size_t i = 0; i < 10; ++i)
    {
        map.add(make_shared<Person>(i + 2, "Bob" + std::to_string(i + 2)), make_shared<int>(i + 2));
        map.add(make_shared<Person>(i * 2, "Jack" + std::to_string(i * 2)), make_shared<int>(i * 2));
    }
    cout << "size=" << map.size() << ", capacity=" << map.capacity() << "\n";
    map.traverse([](shared_ptr<Person> key, shared_ptr<int> value)
    {
        cout << "lamdba<" << *key << "-" << *value << ">\t";
        return false;
    });
    std::getchar();
    return 0;
}

/*
size=5, capacity=16
---------- 1 ----------
<[14, Alice14]-14>
---------- 9 ----------
<[10, Alice10]-10>
---------- 11 ----------
<[11, Alice11]-11>
---------- 13 ----------
<[12, Alice12]-12>
---------- 15 ----------
<[13, Alice13]-13>
delete 0xf16830[11, Alice11]
delete 0xf16b50[11, Alice11]
delete 0xf169d0[13, Alice13]
delete 0xf16810[13, Alice13]
size=3, capacity=16
---------- 1 ----------
<[14, Alice14]-14>
---------- 9 ----------
<[10, Alice10]-10>
---------- 13 ----------
<[12, Alice12]-12>
delete 0xf16760[10, Alice10]
delete 0xf16900[12, Alice12]
delete 0xf16aa0[14, Alice14]
size=3, capacity=16
---------- 1 ----------
<[14, Alice14]-42>
---------- 9 ----------
<[10, Alice10]-30>
---------- 13 ----------
<[12, Alice12]-36>
size=23, capacity=32
---------- 0 ----------
lamdba<[11, Bob11]-11>
---------- 1 ----------
lamdba<[0, Jack0]-0>
lamdba<[3, Bob3]-3>     lamdba<[14, Alice14]-42>
lamdba<[8, Jack8]-8>
---------- 3 ----------
lamdba<[4, Bob4]-4>
---------- 5 ----------
lamdba<[2, Jack2]-2>
lamdba<[5, Bob5]-5>
---------- 7 ----------
lamdba<[6, Bob6]-6>
---------- 8 ----------
lamdba<[10, Jack10]-10>
---------- 9 ----------
lamdba<[4, Jack4]-4>
lamdba<[7, Bob7]-7>     lamdba<[10, Alice10]-30>
---------- 11 ----------
lamdba<[8, Bob8]-8>
---------- 12 ----------
lamdba<[12, Jack12]-12>
---------- 13 ----------
lamdba<[6, Jack6]-6>
lamdba<[9, Bob9]-9>     lamdba<[12, Alice12]-36>
---------- 15 ----------
lamdba<[2, Bob2]-2>
---------- 16 ----------
lamdba<[14, Jack14]-14>
---------- 20 ----------
lamdba<[16, Jack16]-16>
---------- 24 ----------
lamdba<[18, Jack18]-18>
---------- 30 ----------
lamdba<[10, Bob10]-10>
delete 0xf17ea0[11, Bob11]
delete 0xf16ba0[3, Bob3]
delete 0xe025b0[8, Jack8]
delete 0xf168b0[14, Alice14]
delete 0xf16a60[0, Jack0]
delete 0xf16d20[4, Bob4]
delete 0xf16ec0[5, Bob5]
delete 0xf16c50[2, Jack2]
delete 0xe02500[6, Bob6]
delete 0xe027d0[10, Jack10]
delete 0xe02660[7, Bob7]
delete 0xf16830[10, Alice10]
delete 0xf16df0[4, Jack4]
delete 0xe02880[8, Bob8]
delete 0xe02930[12, Jack12]
delete 0xf17c60[9, Bob9]
delete 0xf16740[12, Alice12]
delete 0xf16f70[6, Jack6]
delete 0xf169b0[2, Bob2]
delete 0xf17ba0[14, Jack14]
delete 0xf17f00[16, Jack16]
delete 0xf17960[18, Jack18]
delete 0xf17cc0[10, Bob10]
*/