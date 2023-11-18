/**
 * @file lru-cache.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 146. LRU 缓存
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/lru-cache/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

class LRUCache {
	struct Node {
		int _key = 0, _value = 0;
		shared_ptr<Node> _prev = nullptr, _next = nullptr;

		Node() {}

		Node(int key, int value) {
			_key = key;
			_value = value;
		}
	};

	int _capacity = 0;
	unordered_map<int, shared_ptr<Node>> _map;
	shared_ptr<Node> _head = make_shared<Node>(), _tail = make_shared<Node>();

	void removeNode(shared_ptr<Node> node) {
		node->_next->_prev = node->_prev;
		node->_prev->_next = node->_next;
	}

	void addAfterHead(shared_ptr<Node> node) {
		node->_next = _head->_next;
		_head->_next->_prev = node;
		_head->_next = node;
		node->_prev = _head;
	}

public:
	LRUCache(int capacity) {
		_capacity = capacity;
		_head->_next = _tail;
		_tail->_prev = _head;
	}

	int get(int key) {
		auto iter = _map.find(key);
		if (iter != _map.end()) {
			removeNode(iter->second);
			addAfterHead(iter->second);
			return iter->second->_value;
		}
		return -1;
	}

	void put(int key, int value) {
		auto iter = _map.find(key);
		if (iter != _map.end()) {
			iter->second->_value = value;
			removeNode(iter->second);
			addAfterHead(iter->second);
		}
		else {
			if (_map.size() == _capacity) {
				auto last = _map.find(_tail->_prev->_key);
				removeNode(last->second);
				_map.erase(last);
			}
			shared_ptr<Node> node = make_shared<Node>(key, value);
			_map.emplace(make_pair(key, node));
			addAfterHead(node);
		}
	}
};