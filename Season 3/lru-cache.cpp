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
#include <unordered_map>
#include <memory>
#include <iostream>

using namespace std;

class LRUCache {
    struct Node {
        int pKey = 0, mValue = 0;
        shared_ptr<Node> pPrev = nullptr, pNext = nullptr;

        Node() {}

        Node(int key, int value) {
            pKey = key;
            mValue = value;
        }
    };

    int mCapacity = 0;
    unordered_map<int, shared_ptr<Node>> _map;
    shared_ptr<Node> _head = make_shared<Node>(), _tail = make_shared<Node>();

    void removeNode(shared_ptr<Node> node) {
        node->pNext->pPrev = node->pPrev;
        node->pPrev->pNext = node->pNext;
    }

    void addAfterHead(shared_ptr<Node> node) {
        node->pNext = _head->pNext;
        _head->pNext->pPrev = node;
        _head->pNext = node;
        node->pPrev = _head;
    }

public:
    LRUCache(int capacity) {
        mCapacity = capacity;
        _head->pNext = _tail;
        _tail->pPrev = _head;
    }

    int get(int key) {
        auto iter = _map.find(key);
        if (iter != _map.end()) {
            removeNode(iter->second);
            addAfterHead(iter->second);
            return iter->second->mValue;
        }
        return -1;
    }

    void put(int key, int value) {
        auto iter = _map.find(key);
        if (iter != _map.end()) {
            iter->second->mValue = value;
            removeNode(iter->second);
            addAfterHead(iter->second);
        } else {
            if (_map.size() == mCapacity) {
                auto last = _map.find(_tail->pPrev->pKey);
                removeNode(last->second);
                _map.erase(last);
            }
            shared_ptr<Node> node = make_shared<Node>(key, value);
            _map.emplace(make_pair(key, node));
            addAfterHead(node);
        }
    }
};