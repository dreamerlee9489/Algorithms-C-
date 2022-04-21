#include "./16_LinkedHashMap.h"
#include "./Person.h"
using namespace std;

int main(int argc, char const *argv[])
{
    LinkedHashMap<Person, int> map;
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
    map.traverse();
    return 0;
}

/*
输出：
size=5, capacity=16
<[10, Alice10]-10>
<[11, Alice11]-11>
<[12, Alice12]-12>
<[13, Alice13]-13>
<[14, Alice14]-14>
delete 0xf96850[11, Alice11]
delete 0xf96bb0[11, Alice11]
delete 0xf96a10[13, Alice13]
delete 0xf96830[13, Alice13]
size=3, capacity=16
<[10, Alice10]-10>
<[12, Alice12]-12>
<[14, Alice14]-14>
delete 0xf96770[10, Alice10]
delete 0xf96930[12, Alice12]
delete 0xf96af0[14, Alice14]
size=3, capacity=16
<[10, Alice10]-30>
<[12, Alice12]-36>
<[14, Alice14]-42>
size=23, capacity=32
<[10, Alice10]-30>
<[12, Alice12]-36>
<[14, Alice14]-42>
<[2, Bob2]-2>
<[0, Jack0]-0>
<[3, Bob3]-3>
<[2, Jack2]-2>
<[4, Bob4]-4>
<[4, Jack4]-4>
<[5, Bob5]-5>
<[6, Jack6]-6>
<[6, Bob6]-6>
<[8, Jack8]-8>
<[7, Bob7]-7>
<[10, Jack10]-10>
<[8, Bob8]-8>
<[12, Jack12]-12>
<[9, Bob9]-9>
<[14, Jack14]-14>
<[10, Bob10]-10>
<[16, Jack16]-16>
<[11, Bob11]-11>
<[18, Jack18]-18>
delete 0xf97d30[11, Bob11]
delete 0xf96c10[3, Bob3]
delete 0x25c2350[8, Jack8]
delete 0xf968d0[14, Alice14]
delete 0xf96ab0[0, Jack0]
delete 0xf96d90[4, Bob4]
delete 0x25c2410[5, Bob5]
delete 0xf96cd0[2, Jack2]
delete 0x25c2230[6, Bob6]
delete 0x25c1f90[10, Jack10]
delete 0x25c23b0[7, Bob7]
delete 0xf96850[10, Alice10]
delete 0x25c20b0[4, Jack4]
delete 0x25c2050[8, Bob8]
delete 0x25c1e10[12, Jack12]
delete 0x25c1f30[9, Bob9]
delete 0xf96750[12, Alice12]
delete 0x25c21d0[6, Jack6]
delete 0xf969f0[2, Bob2]
delete 0xf971f0[14, Jack14]
delete 0xf979d0[16, Jack16]
delete 0xf97430[18, Jack18]
delete 0xf97730[10, Bob10]
*/