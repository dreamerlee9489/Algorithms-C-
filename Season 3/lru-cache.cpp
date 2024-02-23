/**
 * @file lru-cache.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 146. LRU 缓存
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/lru-cache/
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_map>

 /**
  * 为了实现一个满足LRU缓存约束的数据结构，我们需要维持一个有序的数据结构来按照元素的使用情况排序。这通常可以通过结合哈希表和双向链表来实现。在C++中，我们可以使用std::unordered_map来实现哈希表，自定义一个双向链表来维护元素的顺序。
  * 解题技巧总结：
  * 使用双向链表：双向链表用于维护缓存项的使用顺序，最近使用的元素会被放到链表的头部，最少使用的元素会被放到链表的尾部。
  * 利用哈希表：哈希表用于存储键和其在双向链表中对应节点的地址，以便于实现O(1)时间复杂度的查询。
  * 定义链表节点：链表节点应包含键、值以及指向前一个节点和后一个节点的指针。
  * 实现get操作：
  * 	如果键不存在于哈希表中，返回-1。
  * 	如果键存在，返回值，并将对应的节点移动到双向链表的头部。
  * 实现put操作：
  * 	如果键存在，更新值，并将对应的节点移动到双向链表的头部。
  * 	如果键不存在：
  * 		如果缓存未满，直接在链表头部插入新节点，并更新哈希表。
  * 		如果缓存已满，删除链表尾部节点，并从哈希表中移除对应的键，然后在链表头部插入新节点，并更新哈希表。
  * 维护链表顺序：每次get或put操作时，如果节点被访问，就将其移动到链表的头部。
  * 逐出元素：如果容量已满，需要逐出最久未使用的元素，即链表的尾部元素。
  *
  */
class LRUCache {
	struct ListNode {
		int key;
		int value;
		ListNode* prev;
		ListNode* next;
		ListNode(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
	};

	int capacity;
	std::unordered_map<int, ListNode*> cache;
	ListNode* head, * tail;

	void addNode(ListNode* node) {
		node->next = head->next;
		node->prev = head;
		head->next->prev = node;
		head->next = node;
	}

	void removeNode(ListNode* node) {
		ListNode* prev = node->prev;
		ListNode* next = node->next;
		prev->next = next;
		next->prev = prev;
	}

	void moveToHead(ListNode* node) {
		removeNode(node);
		addNode(node);
	}

	ListNode* popTail() {
		ListNode* res = tail->prev;
		removeNode(res);
		return res;
	}

public:
	LRUCache(int capacity) : capacity(capacity) {
		head = new ListNode(0, 0);
		tail = new ListNode(0, 0);
		head->next = tail;
		tail->prev = head;
	}

	int get(int key) {
		auto it = cache.find(key);
		if (it == cache.end()) return -1;
		ListNode* node = it->second;
		moveToHead(node);
		return node->value;
	}

	void put(int key, int value) {
		auto it = cache.find(key);
		if (it != cache.end()) {
			ListNode* node = it->second;
			node->value = value;
			moveToHead(node);
		}
		else {
			ListNode* newNode = new ListNode(key, value);
			cache[key] = newNode;
			addNode(newNode);
			if (cache.size() > capacity) {
				ListNode* tail = popTail();
				cache.erase(tail->key);
				delete tail;
			}
		}
	}

	~LRUCache() {
		for (auto it = cache.begin(); it != cache.end(); it++) {
			delete it->second;
		}
		delete head;
		delete tail;
	}
};