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
            _K *pKey = nullptr;
            _V *pValue = nullptr;
            size_t mLevel = 0;
            Node<_K, _V> **pNexts = nullptr;

            friend ostream &operator<<(ostream &out, const Node &node) {
                return out << "[" << *node.pKey << " - " << *node.pValue << "]";
            }

            Node(_K *key, _V *value, size_t level) {
                pKey = key;
                pValue = value;
                mLevel = level;
                pNexts = new Node<_K, _V> *[level]{};
            }

            ~Node() { delete pNexts; }
        };

        using Comparator = int (*)(K *a, K *b);
        const size_t MAX_LEVEL = 32;
        const double P = 0.25;
        size_t mSize = 0;
        int mLevel = 0;
        Node<K, V> *pFirst = nullptr;
        Comparator mComparator = nullptr;

        size_t randomLevel() {
            int level = 1;
            default_random_engine eng;
            uniform_real_distribution<double> dist(0, 1); //均匀实数分布
            while (dist(eng) < P && level < MAX_LEVEL)
                level++;
            return level;
        }

        int compare(K *key1, K *key2) {
            if (mComparator != nullptr)
                return mComparator(key1, key2);
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
            out << "level = " << list.mLevel << "\n";
            for (int i = list.mLevel - 1; i >= 0; i--) {
                Node<K, V> *node = list.pFirst;
                while (node->pNexts[i] != nullptr) {
                    out << node->pNexts[i] << " ";
                    node = node->pNexts[i];
                }
                out << "\n";
            }
            return out << endl;
        }

        SkipList(Comparator comparator = nullptr) {
            mComparator = comparator;
            pFirst = new Node<K, V>(nullptr, nullptr, MAX_LEVEL);
        }

        ~SkipList() { delete pFirst; }

        size_t size() { return mSize; }

        bool isEmpty() { return mSize == 0; }

        V *add(K *key, V *value) {
            checkKey(key);
            Node<K, V> *node = pFirst;
            Node<K, V> **prevs = new Node<K, V> *[mLevel]{};
            for (int i = mLevel - 1; i >= 0; i--) {
                int cmp = -1;
                while (node->pNexts[i] != nullptr && (cmp = compare(key, node->pNexts[i]->pKey)) > 0)
                    node = node->pNexts[i];
                if (cmp == 0) {
                    V *oldV = node->pNexts[i]->pValue;
                    node->pNexts[i]->pValue = value;
                    return oldV;
                }
                prevs[i] = node;
            }
            int newLevel = randomLevel();
            Node<K, V> *newNode = new Node<K, V>(key, value, newLevel);
            for (int i = 0; i < newLevel; i++) {
                if (i >= mLevel)
                    pFirst->pNexts[i] = newNode;
                else {
                    newNode->pNexts[i] = prevs[i]->pNexts[i];
                    prevs[i]->pNexts[i] = newNode;
                }
            }
            mSize++;
            mLevel = max(mLevel, newLevel);
            delete[]prevs, newNode;
            return nullptr;
        }

        V *remove(K *key) {
            checkKey(key);
            Node<K, V> *node = pFirst;
            Node<K, V> **prevs = new Node<K, V> *[mLevel]{};
            bool isExist = false;
            for (int i = mLevel - 1; i >= 0; i--) {
                int cmp = -1;
                while (node->pNexts[i] != nullptr && (cmp = compare(key, node->pNexts[i]->pKey)) > 0)
                    node = node->pNexts[i];
                if (cmp == 0)
                    isExist = true;
                prevs[i] = node;
            }
            if (!isExist)
                return nullptr;
            Node<K, V> *rmvNode = node->pNexts[0];
            for (int i = 0; i < rmvNode->mLevel; i++)
                prevs[i]->pNexts[i] = rmvNode->pNexts[i];
            int newLevel = mLevel;
            while (--newLevel >= 0 && pFirst->pNexts[newLevel] == nullptr)
                mLevel = newLevel;
            mSize--;
            delete[]prevs;
            return rmvNode->pValue;
        }

        V *get(K *key) {
            checkKey(key);
            Node<K, V> *node = pFirst;
            for (int i = mLevel - 1; i >= 0; i--) {
                int cmp = -1;
                while (node->pNexts[i] != nullptr && (cmp = compare(key, node->pNexts[i]->pKey)) > 0)
                    node = node->pNexts[i];
                if (cmp == 0)
                    return node->pNexts[i]->pValue;
            }
            return nullptr;
        }
    };
} // namespace app

#endif /* SKIP_LIST_HPP */
