#ifndef PREFIX_TREE_HPP
#define PREFIX_TREE_HPP

#include <memory>
#include <string>
#include <iostream>
#include "./15_HashMap.hpp"

namespace app {
    /**
     * @brief 前缀树
     * @date 2022-04-23
     * @tparam V
     * @warning 内存泄漏未解决
     */
    template<typename V>
    class Trie {
        template<typename _V>
        struct Node {
            friend bool operator==(const Node &lhs, const Node &rhs) {
                return *lhs.pKey == *rhs.pKey && *lhs.mValue == *rhs.mValue;
            }

            friend ostream &operator<<(ostream &os, const Node &node) {
                return os << "<" << *node.pKey << "-" << *node.mValue << ">";
            }

            bool mWord = false;
            shared_ptr<char> pKey = nullptr;
            shared_ptr<_V> mValue = nullptr;
            shared_ptr<Node<_V>> pParent = nullptr;
            HashMap<char, Node<_V>> *mTree = nullptr;

            Node(shared_ptr<Node<_V>> parent = nullptr) {
                mTree = new HashMap<char, Node<V>>();
                pParent = parent;
            }

            ~Node() { delete mTree; }
        };

        size_t mSize = 0;
        shared_ptr<Node<V>> pRoot = nullptr;

        shared_ptr<Node<V>> get_node(string key) const;

        void key_null_check(string key) const {
            if (key.size() == 0)
                throw invalid_argument("key must not be empty.");
        }

    public:
        Trie() = default;

        ~Trie() { pRoot = nullptr; }

        size_t size() const { return mSize; }

        bool is_empty() const { return mSize == 0; }

        bool start_with(string prefix) const { return get_node(prefix) != nullptr; }

        bool contains(string key) const {
            shared_ptr<Node<V>> node = get_node(key);
            return node != nullptr && node->mWord;
        }

        shared_ptr<V> get(string key) const {
            shared_ptr<Node<V>> node = get_node(key);
            return node != nullptr && node->mWord ? node->mValue : nullptr;
        }

        shared_ptr<V> add(string key, shared_ptr<V> value);

        shared_ptr<V> remove(string key);

        void clear() {
            mSize = 0;
            pRoot = nullptr;
        }
    };

    template<typename V>
    shared_ptr<V> Trie<V>::add(string key, shared_ptr<V> value) {
        key_null_check(key);
        if (pRoot == nullptr)
            pRoot = make_shared<Node<V>>();
        shared_ptr<Node<V>> node = pRoot;
        for (size_t i = 0; i < key.size(); ++i) {
            char ch = key[i];
            shared_ptr<Node<V>> child = node->mTree->getmValue(make_shared<char>(ch));
            if (child == nullptr) {
                child = make_shared<Node<V>>(node);
                child->pKey = make_shared<char>(ch);
                node->mTree->add(child->pKey, child);
            }
            node = child;
        }
        if (node->mWord) {
            shared_ptr<V> old = node->mValue;
            node->mValue = value;
            return old;
        }
        node->mWord = true;
        node->mValue = value;
        mSize++;
        return nullptr;
    }

    template<typename V>
    shared_ptr<V> Trie<V>::remove(string key) {
        shared_ptr<Node<V>> node = get_node(key);
        if (node == nullptr || !node->mWord)
            return nullptr;
        mSize--;
        shared_ptr<V> old = node->mValue;
        if (node->mTree != nullptr && !node->mTree->is_empty()) {
            node->mWord = false;
            node->mValue = nullptr;
            return old;
        }
        shared_ptr<Node<V>> parent = nullptr;
        while ((parent = node->pParent) != nullptr) {
            parent->mTree->remove(node->pKey);
            if (parent->mWord || !parent->mTree->is_empty())
                break;
            node = parent;
        }
        return old;
    }

    template<typename V>
    shared_ptr<typename Trie<V>::template Node<V>> Trie<V>::get_node(string key) const {
        key_null_check(key);
        shared_ptr<Node<V>> node = pRoot;
        for (size_t i = 0; i < key.size(); ++i) {
            if (node == nullptr || node->mTree == nullptr || node->mTree->is_empty())
                return nullptr;
            char ch = key[i];
            node = node->mTree->getmValue(make_shared<char>(ch));
        }
        return node;
    }
} // namespace app

#endif /* PREFIX_TREE_HPP */
