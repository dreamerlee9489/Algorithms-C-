#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP
#include <unordered_map>
#include <iostream>
using namespace std;

namespace app
{
    /**
     * @brief 并查集
     * @date 2022-04-29
     * @tparam K
     */
    template <typename K>
    class DisjointSet
    {
        template <typename _K>
        struct Node
        {
            _K *_key = nullptr;
            Node<_K> *_parent = this;
            size_t _rank = 1;
            Node(_K *key) { _key = key; }
            ~Node() { delete _key; }
        };
        unordered_map<K, Node<K> *> *_map = nullptr;
        Node<K> *find_node(K *key)
        {
            typename unordered_map<K, Node<K> *>::iterator iter = _map->find(*key);
            if (iter != _map->end())
            {
                while (*iter->second->_key != *iter->second->_parent->_key)
                {
                    iter->second->_parent = iter->second->_parent->_parent;
                    iter->second = iter->second->_parent;
                }
                return iter->second;
            }
            return nullptr;
        }

    public:
        DisjointSet() { _map = new unordered_map<K, Node<K> *>(); }
        ~DisjointSet() { delete _map; }
        void add(K *key) { _map->emplace(*key, new Node<K>(key)); }
        K *find_root(K *key)
        {
            Node<K> *node = find_node(key);
            return node != nullptr ? node->_key : nullptr;
        }
        void union_set(K *key1, K *key2)
        {
            Node<K> *p1 = find_node(key1);
            Node<K> *p2 = find_node(key2);
            if (p1 != nullptr && p2 != nullptr)
            {
                if (*p1->_key != *p2->_key)
                {
                    if (p1->_rank < p2->_rank)
                        p1->_parent = p2;
                    else if (p1->_rank > p2->_rank)
                        p2->_parent = p1;
                    else
                    {
                        p1->_parent = p2;
                        p2->_rank += 1;
                    }
                }
            }
        }
        bool is_same(K *key1, K *key2) { return *find_root(key1) == *find_root(key2); }
    };
} // namespace app

#endif /* DISJOINT_SET_HPP */
