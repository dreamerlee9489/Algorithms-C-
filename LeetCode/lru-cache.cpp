/**
 * @file lru-cache.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 146. LRU 缓存
 * @version 0.1
 * @date 2022-07-28
 * @link https://leetcode.cn/problems/lru-cache/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
	list<pair<int, int>> _list;
	unordered_map<int, list<pair<int, int>>::iterator> _map;
	int _capacity = 0;

public:
	LRUCache(int capacity) { _capacity = capacity; }

	int get(int key) {
		auto iter = _map.find(key);
		if (iter == _map.end())
			return -1;
		auto iterPair = _list.emplace(
			_list.end(), make_pair(iter->second->first, iter->second->second));
		_list.erase(iter->second);
		_map[key] = iterPair;
		return iterPair->second;
	}

	void put(int key, int value) {
		auto iter = _map.find(key);
		if (iter != _map.end()) {
			iter->second->second = value;
			auto iterPair = _list.emplace(_list.end(), make_pair(key, value));
			_list.erase(iter->second);
			_map[key] = iterPair;
		}
		else {
			_map.emplace(key, _list.emplace(_list.end(), make_pair(key, value)));
			if (_list.size() > _capacity) {
				_map.erase(_list.begin()->first);
				_list.erase(_list.begin());
			}
		}
	}
};

int main(int argc, char const* argv[]) {
	LRUCache lRUCache = LRUCache(2);
	//    lRUCache.put(1, 1); // 缓存是 {1=1}
	//    lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
	//    cout << lRUCache.get(1) << "\n";    // 返回 1
	//    lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
	//    cout << lRUCache.get(2) << "\n";    // 返回 -1 (未找到)
	//    lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
	//    cout << lRUCache.get(1) << "\n";    // 返回 -1 (未找到)
	//    cout << lRUCache.get(3) << "\n";    // 返回 3
	//    cout << lRUCache.get(4) << "\n";    // 返回 4
	//
	//    lRUCache.put(2, 1);
	//    lRUCache.put(1, 1);
	//    lRUCache.put(2, 3);
	//    lRUCache.put(4, 1);
	//    cout << lRUCache.get(1) << "\n";
	//    cout << lRUCache.get(2) << "\n";

	cout << lRUCache.get(2) << "\n";
	lRUCache.put(2, 6);
	cout << lRUCache.get(1) << "\n";
	lRUCache.put(1, 5);
	lRUCache.put(1, 2);
	cout << lRUCache.get(1) << "\n";
	cout << lRUCache.get(2) << "\n";

	return 0;
}
