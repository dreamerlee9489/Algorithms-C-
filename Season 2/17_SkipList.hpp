#ifndef SKIP_LIST_HPP
#define SKIP_LIST_HPP

#include <cmath>
#include <random>
#include <iostream>

using namespace std;

namespace app {
    /**
     * @brief 跳表
     * @date 2022-07-10 
     * @tparam K
     * @tparam V
     */
    template<typename K, typename V>
    class SkipList {
        template<typename _K, typename _V>
        struct Node {
            _K *_key = nullptr;
            _V *_value = nullptr;
            size_t _level = 0;
            Node<_K, _V> **_nexts = nullptr;

            friend ostream &operator<<(ostream &out, const Node &node) {
                return out << "[" << *node._key << " - " << *node._value << "]";
            }

            Node(_K *key, _V *value, size_t level) {
                _key = key;
                _value = value;
                _level = level;
                _nexts = new Node<_K, _V> *[level]{};
            }

            ~Node() { delete _nexts; }
        };

        using Comparator = int (*)(K *a, K *b);
        const size_t MAX_LEVEL = 32;
        const double P = 0.25;
        size_t _size = 0;
        int _level = 0;
        Node<K, V> *_first = nullptr;
        Comparator _comparator = nullptr;

        size_t randomLevel() {
            int level = 1;
            default_random_engine eng;
            uniform_real_distribution<double> dist(0, 1); //均匀实数分布
            while (dist(eng) < P && level < MAX_LEVEL)
                level++;
            return level;
        }

        int compare(K *key1, K *key2) {
            if (_comparator != nullptr)
                return _comparator(key1, key2);
            else {
                if (*key1 < *key2)
                    return -1;
                else if (*key1 > *key2)
                    return 1;
                return 0;
            }
        }

        void checkKey(K *key) {
            if (key == nullptr)
                throw invalid_argument("key must not be nullptr.");
        }

    public:
        friend ostream &operator<<(ostream &out, const SkipList &list) {
            out << "level = " << list._level << "\n";
            for (int i = list._level - 1; i >= 0; i--) {
                Node<K, V> *node = list._first;
                while (node->_nexts[i] != nullptr) {
                    out << node->_nexts[i] << " ";
                    node = node->_nexts[i];
                }
                out << "\n";
            }
            return out << endl;
        }

        SkipList(Comparator comparator = nullptr) {
            _comparator = comparator;
            _first = new Node<K, V>(nullptr, nullptr, MAX_LEVEL);
        }

        ~SkipList() { delete _first; }

        size_t size() { return _size; }

        bool isEmpty() { return _size == 0; }

        V *add(K *key, V *value) {
            checkKey(key);
            Node<K, V> *node = _first;
            Node<K, V> **prevs = new Node<K, V> *[_level]{};
            for (int i = _level - 1; i >= 0; i--) {
                int cmp = -1;
                while (node->_nexts[i] != nullptr && (cmp = compare(key, node->_nexts[i]->_key)) > 0)
                    node = node->_nexts[i];
                if (cmp == 0) {
                    V *oldV = node->_nexts[i]->_value;
                    node->_nexts[i]->_value = value;
                    return oldV;
                }
                prevs[i] = node;
            }
            int newLevel = randomLevel();
            Node<K, V> *newNode = new Node<K, V>(key, value, newLevel);
            for (int i = 0; i < newLevel; i++) {
                if (i >= _level)
                    _first->_nexts[i] = newNode;
                else {
                    newNode->_nexts[i] = prevs[i]->_nexts[i];
                    prevs[i]->_nexts[i] = newNode;
                }
            }
            _size++;
            _level = max(_level, newLevel);
            delete[]prevs, newNode;
            return nullptr;
        }

        V *remove(K *key) {
            checkKey(key);
            Node<K, V> *node = _first;
            Node<K, V> **prevs = new Node<K, V> *[_level]{};
            bool isExist = false;
            for (int i = _level - 1; i >= 0; i--) {
                int cmp = -1;
                while (node->_nexts[i] != nullptr && (cmp = compare(key, node->_nexts[i]->_key)) > 0)
                    node = node->_nexts[i];
                if (cmp == 0)
                    isExist = true;
                prevs[i] = node;
            }
            if (!isExist)
                return nullptr;
            Node<K, V> *rmvNode = node->_nexts[0];
            for (int i = 0; i < rmvNode->_level; i++)
                prevs[i]->_nexts[i] = rmvNode->_nexts[i];
            int newLevel = _level;
            while (--newLevel >= 0 && _first->_nexts[newLevel] == nullptr)
                _level = newLevel;
            _size--;
            delete[]prevs;
            return rmvNode->_value;
        }

        V *get(K *key) {
            checkKey(key);
            Node<K, V> *node = _first;
            for (int i = _level - 1; i >= 0; i--) {
                int cmp = -1;
                while (node->_nexts[i] != nullptr && (cmp = compare(key, node->_nexts[i]->_key)) > 0)
                    node = node->_nexts[i];
                if (cmp == 0)
                    return node->_nexts[i]->_value;
            }
            return nullptr;
        }
    };
} // namespace app

#endif /* SKIP_LIST_HPP */
