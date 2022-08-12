#ifndef DISJOINT_SET_HPP
#define DISJOINT_SET_HPP

#include <unordered_map>
#include <iostream>

using namespace std;

namespace app {
    /**
     * @brief 并查集
     * @date 2022-04-29
     * @tparam K
     */
    template<typename K>
    class DisjointSet {
        template<typename _K>
        struct Node {
            _K *pKey = nullptr;
            Node<_K> *pParent = this;
            size_t mRank = 1;

            Node(_K *key) { pKey = key; }

            ~Node() { delete pKey; }
        };

        unordered_map<K, Node<K> *> *mMap = nullptr;

        Node<K> *find_node(K *key) {
            typename unordered_map<K, Node<K> *>::iterator iter = mMap->find(*key);
            if (iter != mMap->end()) {
                while (*iter->second->pKey != *iter->second->pParent->pKey) {
                    iter->second->pParent = iter->second->pParent->pParent;
                    iter->second = iter->second->pParent;
                }
                return iter->second;
            }
            return nullptr;
        }

    public:
        DisjointSet() { mMap = new unordered_map<K, Node<K> *>(); }

        ~DisjointSet() { delete mMap; }

        void add(K *key) { mMap->emplace(*key, new Node<K>(key)); }

        K *find_root(K *key) {
            Node<K> *node = find_node(key);
            return node != nullptr ? node->pKey : nullptr;
        }

        void union_set(K *key1, K *key2) {
            Node<K> *p1 = find_node(key1);
            Node<K> *p2 = find_node(key2);
            if (p1 != nullptr && p2 != nullptr) {
                if (*p1->pKey != *p2->pKey) {
                    if (p1->mRank < p2->mRank)
                        p1->pParent = p2;
                    else if (p1->mRank > p2->mRank)
                        p2->pParent = p1;
                    else {
                        p1->pParent = p2;
                        p2->mRank += 1;
                    }
                }
            }
        }

        bool is_same(K *key1, K *key2) { return *find_root(key1) == *find_root(key2); }
    };
} // namespace app

#endif /* DISJOINT_SET_HPP */
