#include "./16_LinkedHashMap.h"
#include "./Person.h"
using namespace app;

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
    cout << "----------Test traverse()----------\n";
    for (size_t i = 0; i < 10; ++i)
    {
        map.add(make_shared<Person>(i + 2, "Bob" + std::to_string(i + 2)), make_shared<int>(i + 2));
        map.add(make_shared<Person>(i * 2, "Jack" + std::to_string(i * 2)), make_shared<int>(i * 2));
    }
    cout << "size=" << map.size() << ", capacity=" << map.capacity() << "\n";
    map.traverse();
    cout << "----------Test HashMap(const LinkedHashMap<K, V> &)----------\n";
    LinkedHashMap<Person, int> map1 = LinkedHashMap<Person, int>(map);
    cout << "size=" << map1.size() << ", capacity=" << map1.capacity() << "\n";
    map1.traverse();
    cout << "----------Test HashMap(LinkedHashMap<K, V> &&)----------\n";
    LinkedHashMap<Person, int> map2 = LinkedHashMap<Person, int>(std::move(map));
    cout << "size=" << map2.size() << ", capacity=" << map2.capacity() << "\n";
    map2.traverse();
    return 0;
}

/*
size=5, capacity=16
<[10, Alice10]-10>
<[11, Alice11]-11>
<[12, Alice12]-12>
<[13, Alice13]-13>
<[14, Alice14]-14>
delete 0xed6850[11, Alice11]
delete 0xed6bb0[11, Alice11]
delete 0xed6a10[13, Alice13]
delete 0xed6830[13, Alice13]
size=3, capacity=16
<[10, Alice10]-10>
<[12, Alice12]-12>
<[14, Alice14]-14>
delete 0xed6770[10, Alice10]
delete 0xed6930[12, Alice12]
delete 0xed6af0[14, Alice14]
size=3, capacity=16
<[10, Alice10]-30>
<[12, Alice12]-36>
<[14, Alice14]-42>
----------Test traverse()----------
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
----------Test HashMap(const LinkedHashMap<K, V> &)----------
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
----------Test HashMap(LinkedHashMap<K, V> &&)----------
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

delete 0xed7550[11, Bob11]
delete 0x2691d50[8, Jack8]
delete 0xed6c10[3, Bob3]
delete 0xed6d90[4, Bob4]
delete 0x2692290[5, Bob5]
delete 0x2691cf0[6, Bob6]
delete 0x2691e10[10, Jack10]
delete 0x2691ff0[7, Bob7]
delete 0xed6850[10, Alice10]
delete 0x2692110[8, Bob8]
delete 0x2692170[12, Jack12]
delete 0x26922f0[9, Bob9]
delete 0xed6750[12, Alice12]
delete 0xed7010[14, Jack14]
delete 0xed6ab0[0, Jack0]
delete 0xed68d0[14, Alice14]
delete 0xed7070[16, Jack16]
delete 0xed6cd0[2, Jack2]
delete 0xed7730[18, Jack18]
delete 0x2692230[4, Jack4]
delete 0x26920b0[6, Jack6]
delete 0xed7e50[10, Bob10]
delete 0xed69f0[2, Bob2]
*/