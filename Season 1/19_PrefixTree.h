#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H
#include <memory>
#include <string>
#include <iostream>
#include "./15_HashMap.h"
/**
 * @brief 前缀树
 * @date 2022-04-23
 * @tparam V 
 * @warning 内存泄漏未解决
 */
template <typename V>
class PrefixTree 
{
    template <typename _V>
    struct Node
    {
        friend bool operator==(const Node &lhs, const Node &rhs) { return *lhs._key == *rhs._key && *lhs._value == *rhs._value; }
        friend std::ostream &operator<<(std::ostream &os, const Node &node) { return os << "<" << *node._key << "-" << *node._value << ">"; }
        bool _word = false;
        std::shared_ptr<char> _key = nullptr;
        std::shared_ptr<_V> _value = nullptr;
        std::shared_ptr<Node<_V>> _parent = nullptr;
        HashMap<char, Node<_V>> *_tree = nullptr;
        Node(std::shared_ptr<Node<_V>> parent = nullptr)
        {
            _tree = new HashMap<char, Node<V>>();
            _parent = parent;
        }
        ~Node() { delete _tree; }
    };
    size_t _size = 0;
    std::shared_ptr<Node<V>> _root = nullptr;
    std::shared_ptr<Node<V>> get_node(std::string key) const;
    void key_null_check(std::string key) const
    {
        if (key.size() == 0)
            throw std::invalid_argument("key must not be empty.");
    }

public:
    PrefixTree() = default;
    ~PrefixTree() { _root = nullptr; }
    size_t size() const { return _size; }
    bool is_empty() const { return _size == 0; }
    bool start_with(std::string prefix) const { return get_node(prefix) != nullptr; }
    bool contains(std::string key) const
    {
        std::shared_ptr<Node<V>> node = get_node(key);
        return node != nullptr && node->_word;
    }
    std::shared_ptr<V> get(std::string key) const
    {
        std::shared_ptr<Node<V>> node = get_node(key);
        return node != nullptr && node->_word ? node->_value : nullptr;
    }
    std::shared_ptr<V> add(std::string key, std::shared_ptr<V> value);
    std::shared_ptr<V> remove(std::string key);
    void clear()
    {
        _size = 0;
        _root = nullptr;
    }
};

template <typename V>
std::shared_ptr<V> PrefixTree<V>::add(std::string key, std::shared_ptr<V> value)
{
    key_null_check(key);
    if(_root == nullptr)
        _root = std::make_shared<Node<V>>();
    std::shared_ptr<Node<V>> node = _root;
    for(size_t i = 0; i < key.size(); ++i)
    {
        char ch = key[i];
        std::shared_ptr<Node<V>> child = node->_tree->get_value(std::make_shared<char>(ch));
        if(child == nullptr)
        {
            child = std::make_shared<Node<V>>(node);
            child->_key = std::make_shared<char>(ch);
            node->_tree->add(child->_key, child);
        }
        node = child;
    }
    if(node->_word)
    {
        std::shared_ptr<V> old = node->_value;
        node->_value = value;
        return old;
    }
    node->_word = true;
    node->_value = value;
    _size++;
    return nullptr;
}

template <typename V>
std::shared_ptr<V> PrefixTree<V>::remove(std::string key)
{
    std::shared_ptr<Node<V>> node = get_node(key);
    if(node == nullptr || !node->_word)
        return nullptr;
    _size--;
    std::shared_ptr<V> old = node->_value;
    if(node->_tree != nullptr && !node->_tree->is_empty())
    {
        node->_word = false;
        node->_value = nullptr;
        return old;
    }
    std::shared_ptr<Node<V>> parent = nullptr;
    while ((parent = node->_parent) != nullptr)
    {
        parent->_tree->remove(node->_key);
        if(parent->_word || !parent->_tree->is_empty())
            break;
        node = parent;
    }
    return old;
}

template <typename V>
std::shared_ptr<typename PrefixTree<V>::template Node<V>> PrefixTree<V>::get_node(std::string key) const 
{
    key_null_check(key);
    std::shared_ptr<Node<V>> node = _root;
    for (size_t i = 0; i < key.size(); ++i)
    {
        if(node == nullptr || node->_tree == nullptr || node->_tree->is_empty())
            return nullptr;
        char ch = key[i];
        node = node->_tree->get_value(std::make_shared<char>(ch));
    }
    return node;
}

#endif /* PREFIX_TREE_H */
