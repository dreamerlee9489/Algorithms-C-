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
                return *lhs._key == *rhs._key && *lhs._value == *rhs._value;
            }

            friend ostream &operator<<(ostream &os, const Node &node) {
                return os << "<" << *node._key << "-" << *node._value << ">";
            }

            bool _word = false;
            shared_ptr<char> _key = nullptr;
            shared_ptr<_V> _value = nullptr;
            shared_ptr<Node<_V>> _parent = nullptr;
            HashMap<char, Node<_V>> *_tree = nullptr;

            Node(shared_ptr<Node<_V>> parent = nullptr) {
                _tree = new HashMap<char, Node<V>>();
                _parent = parent;
            }

            ~Node() { delete _tree; }
        };

        size_t _size = 0;
        shared_ptr<Node<V>> _root = nullptr;

        shared_ptr<Node<V>> get_node(string key) const;

        void key_null_check(string key) const {
            if (key.size() == 0)
                throw invalid_argument("key must not be empty.");
        }

    public:
        Trie() = default;

        ~Trie() { _root = nullptr; }

        size_t size() const { return _size; }

        bool is_empty() const { return _size == 0; }

        bool start_with(string prefix) const { return get_node(prefix) != nullptr; }

        bool contains(string key) const {
            shared_ptr<Node<V>> node = get_node(key);
            return node != nullptr && node->_word;
        }

        shared_ptr<V> get(string key) const {
            shared_ptr<Node<V>> node = get_node(key);
            return node != nullptr && node->_word ? node->_value : nullptr;
        }

        shared_ptr<V> add(string key, shared_ptr<V> value);

        shared_ptr<V> remove(string key);

        void clear() {
            _size = 0;
            _root = nullptr;
        }
    };

    template<typename V>
    shared_ptr<V> Trie<V>::add(string key, shared_ptr<V> value) {
        key_null_check(key);
        if (_root == nullptr)
            _root = make_shared<Node<V>>();
        shared_ptr<Node<V>> node = _root;
        for (size_t i = 0; i < key.size(); ++i) {
            char ch = key[i];
            shared_ptr<Node<V>> child = node->_tree->get_value(make_shared<char>(ch));
            if (child == nullptr) {
                child = make_shared<Node<V>>(node);
                child->_key = make_shared<char>(ch);
                node->_tree->add(child->_key, child);
            }
            node = child;
        }
        if (node->_word) {
            shared_ptr<V> old = node->_value;
            node->_value = value;
            return old;
        }
        node->_word = true;
        node->_value = value;
        _size++;
        return nullptr;
    }

    template<typename V>
    shared_ptr<V> Trie<V>::remove(string key) {
        shared_ptr<Node<V>> node = get_node(key);
        if (node == nullptr || !node->_word)
            return nullptr;
        _size--;
        shared_ptr<V> old = node->_value;
        if (node->_tree != nullptr && !node->_tree->is_empty()) {
            node->_word = false;
            node->_value = nullptr;
            return old;
        }
        shared_ptr<Node<V>> parent = nullptr;
        while ((parent = node->_parent) != nullptr) {
            parent->_tree->remove(node->_key);
            if (parent->_word || !parent->_tree->is_empty())
                break;
            node = parent;
        }
        return old;
    }

    template<typename V>
    shared_ptr<typename Trie<V>::template Node<V>> Trie<V>::get_node(string key) const {
        key_null_check(key);
        shared_ptr<Node<V>> node = _root;
        for (size_t i = 0; i < key.size(); ++i) {
            if (node == nullptr || node->_tree == nullptr || node->_tree->is_empty())
                return nullptr;
            char ch = key[i];
            node = node->_tree->get_value(make_shared<char>(ch));
        }
        return node;
    }
} // namespace app

#endif /* PREFIX_TREE_HPP */
