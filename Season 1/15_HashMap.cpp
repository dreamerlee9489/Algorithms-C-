#include "./15_HashMap.hpp"
#include "./Person.hpp"

using namespace app;

int main(int argc, char const* argv[]) {
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
	cout << "----------Test traverse()----------\n";
	for (size_t i = 0; i < 10; ++i) {
		map.add(make_shared<Person>(i + 2, "Bob" + std::to_string(i + 2)),
			make_shared<int>(i + 2));
		map.add(make_shared<Person>(i * 2, "Jack" + std::to_string(i * 2)),
			make_shared<int>(i * 2));
	}
	cout << "size=" << map.size() << ", capacity=" << map.capacity() << "\n";
	map.traverse([](shared_ptr<Person> key, shared_ptr<int> value) {
		cout << "lamdba<" << *key << "-" << *value << ">\t";
		return false;
		});
	cout << "----------Test HashMap(const HashMap<K, V> &)----------\n";
	HashMap<Person, int> map1 = HashMap<Person, int>(map);
	cout << "size=" << map1.size() << ", capacity=" << map1.capacity() << "\n";
	map1.traverse();
	cout << "----------Test HashMap(HashMap<K, V> &&)----------\n";
	HashMap<Person, int> map2 = HashMap<Person, int>(std::move(map));
	cout << "size=" << map2.size() << ", capacity=" << map2.capacity() << "\n";
	map2.traverse();
	return 0;
}

/*
size=5, capacity=16
---------- 4 ----------
<[12, Alice12]-12>
---------- 8 ----------
<[14, Alice14]-14>
---------- 9 ----------
<[13, Alice13]-13>
---------- 11 ----------
<[11, Alice11]-11>
---------- 13 ----------
<[10, Alice10]-10>
delete 0x25f2210[11, Alice11]
delete 0x9c7620[11, Alice11]
delete 0x25f24f0[13, Alice13]
delete 0x9c76a0[13, Alice13]
size=3, capacity=16
---------- 4 ----------
<[12, Alice12]-12>
---------- 8 ----------
<[14, Alice14]-14>
---------- 13 ----------
<[10, Alice10]-10>
delete 0x25f20a0[10, Alice10]
delete 0x25f2380[12, Alice12]
delete 0x25f2e10[14, Alice14]
size=3, capacity=16
---------- 4 ----------
<[12, Alice12]-36>
---------- 8 ----------
<[14, Alice14]-42>
---------- 13 ----------
<[10, Alice10]-30>
----------Test traverse()----------
size=23, capacity=32
---------- 2 ----------
lamdba<[6, Jack6]-6>
---------- 3 ----------
lamdba<[8, Bob8]-8>
---------- 4 ----------
lamdba<[12, Alice12]-36>
lamdba<[2, Jack2]-2>
---------- 6 ----------
lamdba<[18, Jack18]-18>
---------- 7 ----------
lamdba<[14, Jack14]-14>
lamdba<[11, Bob11]-11>
---------- 8 ----------
lamdba<[14, Alice14]-42>
lamdba<[4, Bob4]-4>     lamdba<[6, Bob6]-6>
---------- 9 ----------
lamdba<[5, Bob5]-5>
---------- 10 ----------
lamdba<[4, Jack4]-4>
---------- 12 ----------
lamdba<[2, Bob2]-2>
lamdba<[3, Bob3]-3>
---------- 13 ----------
lamdba<[10, Alice10]-30>
lamdba<[8, Jack8]-8>
---------- 14 ----------
lamdba<[0, Jack0]-0>
---------- 15 ----------
lamdba<[16, Jack16]-16>
---------- 20 ----------
lamdba<[12, Jack12]-12>
---------- 21 ----------
lamdba<[10, Jack10]-10>
lamdba<[9, Bob9]-9>
---------- 24 ----------
lamdba<[7, Bob7]-7>
---------- 25 ----------
lamdba<[10, Bob10]-10>
----------Test HashMap(const HashMap<K, V> &)----------
size=23, capacity=32
---------- 2 ----------
<[6, Jack6]-6>
---------- 3 ----------
<[8, Bob8]-8>
---------- 4 ----------
<[12, Alice12]-36>
<[2, Jack2]-2>
---------- 6 ----------
<[18, Jack18]-18>
---------- 7 ----------
<[14, Jack14]-14>
<[11, Bob11]-11>
---------- 8 ----------
<[14, Alice14]-42>
<[4, Bob4]-4>   <[6, Bob6]-6>
---------- 9 ----------
<[5, Bob5]-5>
---------- 10 ----------
<[4, Jack4]-4>
---------- 12 ----------
<[2, Bob2]-2>
---------- 13 ----------
<[10, Alice10]-30>
<[8, Jack8]-8>
---------- 15 ----------
<[16, Jack16]-16>
---------- 20 ----------
<[12, Jack12]-12>
---------- 21 ----------
<[10, Jack10]-10>
<[9, Bob9]-9>
---------- 24 ----------
<[7, Bob7]-7>
---------- 25 ----------
<[10, Bob10]-10>
---------- 28 ----------
<[3, Bob3]-3>
---------- 30 ----------
<[0, Jack0]-0>
----------Test HashMap(HashMap<K, V> &&)----------
size=23, capacity=32
---------- 2 ----------
<[6, Jack6]-6>
---------- 3 ----------
<[8, Bob8]-8>
---------- 4 ----------
<[12, Alice12]-36>
<[2, Jack2]-2>
---------- 6 ----------
<[18, Jack18]-18>
---------- 7 ----------
<[14, Jack14]-14>
<[11, Bob11]-11>
---------- 8 ----------
<[14, Alice14]-42>
<[4, Bob4]-4>   <[6, Bob6]-6>
---------- 9 ----------
<[5, Bob5]-5>
---------- 10 ----------
<[4, Jack4]-4>
---------- 12 ----------
<[2, Bob2]-2>
<[3, Bob3]-3>
---------- 13 ----------
<[10, Alice10]-30>
<[8, Jack8]-8>
---------- 14 ----------
<[0, Jack0]-0>
---------- 15 ----------
<[16, Jack16]-16>
---------- 20 ----------
<[12, Jack12]-12>
---------- 21 ----------
<[10, Jack10]-10>
<[9, Bob9]-9>
---------- 24 ----------
<[7, Bob7]-7>
---------- 25 ----------
<[10, Bob10]-10>
delete 0x9c8ba0[6, Jack6]
delete 0x9c88a0[8, Bob8]
delete 0x9c89a0[2, Jack2]
delete 0x9c7a60[12, Alice12]
delete 0x9c8da0[18, Jack18]
delete 0x9c8f20[11, Bob11]
delete 0x9c8620[14, Jack14]
delete 0x9c8820[4, Bob4]
delete 0x9c8420[6, Bob6]
delete 0x9c7ae0[14, Alice14]
delete 0x9c8c20[5, Bob5]
delete 0x9c87a0[4, Jack4]
delete 0x9c7e20[2, Bob2]
delete 0x9c8220[8, Jack8]
delete 0x9c79e0[10, Alice10]
delete 0x9c8520[16, Jack16]
delete 0x9c83a0[12, Jack12]
delete 0x9c8aa0[9, Bob9]
delete 0x9c81a0[10, Jack10]
delete 0x9c8a20[7, Bob7]
delete 0x9c8ca0[10, Bob10]
delete 0x9c8040[3, Bob3]
delete 0x9c7f30[0, Jack0]
*/