#include "./13_HashMap.h"
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
    cout << "size=" << map.size() << "\n";
    map.traverse();
    map.remove(make_shared<Person>(11, "Alice11"));
    map.remove(make_shared<Person>(13, "Alice13"));
    cout << "size=" << map.size() << "\n";
    map.traverse();
    map.add(make_shared<Person>(10, "Alice10"), make_shared<int>(30));
    map.add(make_shared<Person>(12, "Alice12"), make_shared<int>(36));
    map.add(make_shared<Person>(14, "Alice14"), make_shared<int>(42));
    cout << "size=" << map.size() << "\n";
    map.traverse();
    for (size_t i = 0; i < 10; ++i)
    {
        map.add(make_shared<Person>(i + 2, "Bob" + std::to_string(i + 2)), make_shared<int>(i + 2));
        map.add(make_shared<Person>(i * 2, "Jack" + std::to_string(i * 2)), make_shared<int>(i * 2));
    }
    cout << "size=" << map.size() << "\n";
    map.traverse();
    return 0;
}

/*
输出：
size=5
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
delete 0x696bb0[11, Alice11]
delete 0x696bb0[13, Alice13]
size=3
---------- 1 ----------
<[14, Alice14]-14>
---------- 9 ----------
<[10, Alice10]-10>
---------- 13 ----------
<[12, Alice12]-12>
delete 0x696810[10, Alice10]
delete 0x696990[12, Alice12]
delete 0x696b10[14, Alice14]
size=3
---------- 1 ----------
<[14, Alice14]-42>
---------- 9 ----------
<[10, Alice10]-30>
---------- 13 ----------
<[12, Alice12]-36>
size=23
---------- 0 ----------
<[11, Bob11]-11>
---------- 1 ----------
<[0, Jack0]-0>
<[3, Bob3]-3>
<[14, Alice14]-42>
<[8, Jack8]-8>
---------- 3 ----------
<[4, Bob4]-4>
---------- 5 ----------
<[2, Jack2]-2>
<[5, Bob5]-5>
---------- 7 ----------
<[6, Bob6]-6>
---------- 8 ----------
<[10, Jack10]-10>
---------- 9 ----------
<[4, Jack4]-4>
<[7, Bob7]-7>
<[10, Alice10]-30>
---------- 11 ----------
<[8, Bob8]-8>
---------- 12 ----------
<[12, Jack12]-12>
---------- 13 ----------
<[6, Jack6]-6>
<[9, Bob9]-9>
<[12, Alice12]-36>
---------- 15 ----------
<[2, Bob2]-2>
---------- 16 ----------
<[14, Jack14]-14>
---------- 20 ----------
<[16, Jack16]-16>
---------- 24 ----------
<[18, Jack18]-18>
---------- 30 ----------
<[10, Bob10]-10>
delete 0x6977b0[11, Bob11]
delete 0x696d50[3, Bob3]
delete 0x6b2100[8, Jack8]
delete 0x696990[14, Alice14]
delete 0x696c90[0, Jack0]
delete 0x6b1e30[4, Bob4]
delete 0x6b1d90[5, Bob5]
delete 0x6b2330[2, Jack2]
delete 0x6b2060[6, Bob6]
delete 0x6b23d0[10, Jack10]
delete 0x6b2420[7, Bob7]
delete 0x696bd0[10, Alice10]
delete 0x6b1ed0[4, Jack4]
delete 0x6b2380[8, Bob8]
delete 0x6b1de0[12, Jack12]
delete 0x6b1f20[9, Bob9]
delete 0x696810[12, Alice12]
delete 0x6b20b0[6, Jack6]
delete 0x696b10[2, Bob2]
delete 0x697df0[14, Jack14]
delete 0x697da0[16, Jack16]
delete 0x697490[18, Jack18]
delete 0x697b20[10, Bob10]
*/