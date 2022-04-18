/**
 * @file 12_TreeMap.h
 * @author dreamerlee9489@outlook.com
 * @brief 基于红黑树的映射
 * @version 0.1
 * @date 2022-04-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef MAP_H
#define MAP_H
#include <memory>
#include <queue>
#include "./IString.h"

template <typename K, typename V>
class TreeMap
{
    using TraverseFunc = bool (*)(std::shared_ptr<K> key);
    using Comparator = int (*)(std::shared_ptr<K> a, std::shared_ptr<K> b);
    static const bool BLACK = false, RED = true;
    template <typename _K, typename _V>
    struct Node : public IString
    {
        friend std::ostream &operator<<(std::ostream &os, const Node<_K, _V> &node) { return os << node.to_string(); }
        std::shared_ptr<_K> _key;
        std::shared_ptr<_V> _value;
        bool _color = RED;
        Node<_K, _V> *_parent = nullptr, *_left = nullptr, *_right = nullptr;
        Node<_K, _V> &operator=(const Node<_K, _V> &node);
        Node<_K, _V> &operator=(Node<_K, _V> &&node) noexcept;
        Node(std::shared_ptr<_K> key, std::shared_ptr<_V> value, Node<_K, _V> *parent = nullptr, Node<_K, _V> *left = nullptr, Node<_K, _V> *right = nullptr)
            : _key(key), _value(value), _parent(parent), _left(left), _right(right) {}
        Node(const Node<_K, _V> &node) { *this = node; }
        Node(Node<_K, _V> &&node) noexcept { *this = std::move(node); }
        virtual ~Node();
        bool is_leaf() const { return _left == nullptr && _right == nullptr; }
        bool is_binary() const { return _left != nullptr && _right != nullptr; }
        bool is_left() const { return _parent != nullptr && this == _parent->_left; }
        bool is_right() const { return _parent != nullptr && this == _parent->_right; }
        Node<_K, _V> *get_sibling() const;
        std::string to_string() const override { return ((IString &)*_key).to_string(); }
    };
    size_t _size = 0;
    Node<K, V> *_root = nullptr;
    Comparator _comparator = nullptr;
    void not_null_check(std::shared_ptr<K> key) const;
    Node<K, V> *get_node(std::shared_ptr<K> key) const;
    Node<K, V> *get_predecessor(Node<K, V> *node) const;
    Node<K, V> *get_successor(Node<K, V> *node) const;
    void after_add(Node<K, V> *node);
    void after_remove(Node<K, V> *node);
    void rotate_left(Node<K, V> *grand);
    void rotate_right(Node<K, V> *grand);
    void after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child);
    Node<K, V> *set_color(Node<K, V> *node, bool color);
    bool color_of(Node<K, V> *node) { return node == nullptr ? BLACK : node->_color; }
    bool is_black(Node<K, V> *node) { return color_of(node) == BLACK; }
    bool is_red(Node<K, V> *node) { return color_of(node) == RED; }
    void inorder_traverse(Node<K, V> *node, TraverseFunc func = nullptr) const;
    void clear_recu(Node<K, V> *node);

public:
    TreeMap<K, V> &operator=(const TreeMap<K, V> &map);
    TreeMap<K, V> &operator=(TreeMap<K, V> &&map);
    TreeMap(Comparator comparator = nullptr) { _comparator = comparator; }
    TreeMap(const TreeMap<K, V> &map) { *this = map; }
    TreeMap(TreeMap<K, V> &&map) { *this = std::move(map); }
    ~TreeMap() { clear_recu(_root); }
    size_t size() const { return _size; }
    bool is_empty() const { return _size == 0; }
    bool contains_key(std::shared_ptr<K> key) { return get_node(key) != nullptr; }
    bool contains_value(std::shared_ptr<V> value);
    std::shared_ptr<V> get_value(std::shared_ptr<K> key);
    std::shared_ptr<V> add(std::shared_ptr<K> key, std::shared_ptr<V> value);
    std::shared_ptr<V> remove(std::shared_ptr<K> key);
    void traverse(TraverseFunc func = nullptr) const { inorder_traverse(_root, func); }
    void clear();
};

template <typename K, typename V>
template <typename _K, typename _V>
inline TreeMap<K, V>::Node<_K, _V> &TreeMap<K, V>::Node<_K, _V>::operator=(const Node<_K, _V> &node)
{
    _key = node._key;
    _value = node._value;
    _parent = node._parent;
    _left = node._left;
    _right = node._right;
    _color = node._color;
    return *this;
}

template <typename K, typename V>
template <typename _K, typename _V>
inline TreeMap<K, V>::Node<_K, _V> &TreeMap<K, V>::Node<_K, _V>::operator=(Node<_K, _V> &&node) noexcept
{
    _key = nullptr;
    _value = nullptr;
    this = &node;
    return *this;
}

template <typename K, typename V>
template <typename _K, typename _V>
inline TreeMap<K, V>::Node<_K, _V>::~Node()
{
    _key = nullptr;
    _value = nullptr;
}

template <typename K, typename V>
template <typename _K, typename _V>
inline TreeMap<K, V>::Node<_K, _V> *TreeMap<K, V>::Node<_K, _V>::get_sibling() const
{
    if (is_left())
        return _parent->_right;
    else if (is_right())
        return _parent->_left;
    return nullptr;
}

template <typename K, typename V>
inline TreeMap<K, V> &TreeMap<K, V>::operator=(const TreeMap<K, V> &map)
{
    clear();
    if (map._size > 0)
    {
        _comparator = map._comparator;
        std::queue<Node<K, V> *> q = std::queue<Node<K, V> *>();
        q.push(map._root);
        while (!q.empty())
        {
            Node<K, V> *node = q.front();
            add(node->_key, node->_value);
            q.pop();
            if (node->_left != nullptr)
                q.push(node->_left);
            if (node->_right != nullptr)
                q.push(node->_right);
        }
    }
    return *this;
}

template <typename K, typename V>
inline TreeMap<K, V> &TreeMap<K, V>::operator=(TreeMap<K, V> &&map)
{
    clear();
    _size = map._size;
    _root = map._root;
    _comparator = map._comparator;
    map._size = 0;
    map._root = nullptr;
    map._comparator = nullptr;
    return *this;
}

template <typename K, typename V>
inline void TreeMap<K, V>::not_null_check(std::shared_ptr<K> key) const
{
    if (key == nullptr)
        throw std::invalid_argument("key must be not null.");
}

template <typename K, typename V>
inline TreeMap<K, V>::Node<K, V> *TreeMap<K, V>::get_node(std::shared_ptr<K> key) const
{
    Node<K, V> *node = _root;
    while (node != nullptr)
    {
        if (_comparator == nullptr)
        {
            if (*node->_key < *key)
                node = node->_right;
            else if (*node->_key > *key)
                node = node->_left;
            else
                return node;
        }
        else
        {
            if (_comparator(node->_key, key) < 0)
                node = node->_right;
            else if (_comparator(node->_key, key) > 0)
                node = node->_left;
            else
                return node;
        }
    }
    return nullptr;
}

template <typename K, typename V>
inline TreeMap<K, V>::Node<K, V> *TreeMap<K, V>::get_predecessor(Node<K, V> *node) const
{
    if (node != nullptr)
    {
        Node<K, V> *p = node->_left;
        if (p != nullptr)
        {
            while (p->_right != nullptr)
                p = p->_right;
            return p;
        }
        while (node->_parent != nullptr && node == node->_parent->_left)
            node = node->_parent;
        return node->_parent;
    }
    return nullptr;
}

template <typename K, typename V>
inline TreeMap<K, V>::Node<K, V> *TreeMap<K, V>::get_successor(Node<K, V> *node) const
{
    if (node != nullptr)
    {
        Node<K, V> *p = node->_right;
        if (p != nullptr)
        {
            while (p->_left != nullptr)
                p = p->_left;
            return p;
        }
        while (node->_parent != nullptr && node == node->_parent->_right)
            node = node->_parent;
        return node->_parent;
    }
    return nullptr;
}

template <typename K, typename V>
inline void TreeMap<K, V>::after_add(Node<K, V> *node)
{
    Node<K, V> *parent = node->_parent;
    if (parent == nullptr)
    {
        set_color(node, BLACK);
        return;
    }
    if (is_red(parent))
    {
        Node<K, V> *uncle = parent->get_sibling();
        Node<K, V> *grand = set_color(parent->_parent, RED);
        if (is_red(uncle))
        {
            set_color(parent, BLACK);
            set_color(uncle, BLACK);
            after_add(grand);
            return;
        }
        if (parent->is_left())
        {
            if (node->is_left())
                set_color(parent, BLACK);
            else
            {
                set_color(node, BLACK);
                rotate_left(parent);
            }
            rotate_right(grand);
        }
        else
        {
            if (node->is_left())
            {
                set_color(node, BLACK);
                rotate_right(parent);
            }
            else
                set_color(parent, BLACK);
            rotate_left(grand);
        }
    }
}

template <typename K, typename V>
inline void TreeMap<K, V>::after_remove(Node<K, V> *node)
{
    if (is_red(node))
    {
        set_color(node, BLACK);
        return;
    }
    Node<K, V> *parent = node->_parent;
    if (parent != nullptr)
    {
        bool is_left = parent->_left == nullptr || node->is_left();
        Node<K, V> *sibling = is_left ? parent->_right : parent->_left;
        if (is_left)
        {
            if (is_red(sibling))
            {
                set_color(sibling, BLACK);
                set_color(parent, RED);
                rotate_left(parent);
                sibling = parent->_right;
            }
            if (is_black(sibling->_left) && is_black(sibling->_right))
            {
                bool parent_black = is_black(parent);
                set_color(parent, BLACK);
                set_color(sibling, RED);
                if (parent_black)
                    after_remove(parent);
            }
            else
            {
                if (is_black(sibling->_right))
                {
                    rotate_right(sibling);
                    sibling = parent->_right;
                }
                set_color(sibling, color_of(parent));
                set_color(sibling->_right, BLACK);
                set_color(parent, BLACK);
                rotate_left(parent);
            }
        }
        else
        {
            if (is_red(sibling))
            {
                set_color(sibling, BLACK);
                set_color(parent, RED);
                rotate_right(parent);
                sibling = parent->_left;
            }
            if (is_black(sibling->_left) && is_black(sibling->_right))
            {
                bool parent_black = is_black(parent);
                set_color(parent, BLACK);
                set_color(sibling, RED);
                if (parent_black)
                    after_remove(parent);
            }
            else
            {
                if (is_black(sibling->_left))
                {
                    rotate_left(sibling);
                    sibling = parent->_left;
                }
                set_color(sibling, color_of(parent));
                set_color(sibling->_left, BLACK);
                set_color(parent, BLACK);
                rotate_right(parent);
            }
        }
    }
}

template <typename K, typename V>
inline void TreeMap<K, V>::rotate_left(Node<K, V> *grand)
{
    Node<K, V> *parent = grand->_right;
    Node<K, V> *child = parent->_left;
    grand->_right = child;
    parent->_left = grand;
    after_rotate(grand, parent, child);
}

template <typename K, typename V>
inline void TreeMap<K, V>::rotate_right(Node<K, V> *grand)
{
    Node<K, V> *parent = grand->_left;
    Node<K, V> *child = parent->_right;
    grand->_left = child;
    parent->_right = grand;
    after_rotate(grand, parent, child);
}

template <typename K, typename V>
inline void TreeMap<K, V>::after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child)
{
    parent->_parent = grand->_parent;
    if (grand->is_left())
        grand->_parent->_left = parent;
    else if (grand->is_right())
        grand->_parent->_right = parent;
    else
        _root = parent;
    if (child != nullptr)
        child->_parent = grand;
    grand->_parent = parent;
}

template <typename K, typename V>
inline TreeMap<K, V>::Node<K, V> *TreeMap<K, V>::set_color(Node<K, V> *node, bool color)
{
    if (node != nullptr)
        node->_color = color;
    return node;
}

template <typename K, typename V>
inline void TreeMap<K, V>::clear_recu(Node<K, V> *node)
{
    if (node != nullptr)
    {
        clear_recu(node->_left);
        clear_recu(node->_right);
        delete node;
    }
}

template <typename K, typename V>
inline bool TreeMap<K, V>::contains_value(std::shared_ptr<V> value)
{
    if (_root != nullptr)
    {
        std::queue<Node<K, V> *> q = new std::queue<Node<K, V> *>();
        q.push(_root);
        while (!q.empty())
        {
            Node<K, V> *node = q.front();
            q.pop();
            if (node->_left != nullptr)
                q.push(node->_left);
            if (node->_right != nullptr)
                q.push(node->_right);
            if (_comparator == nullptr)
            {
                if (*node->_value == *value)
                    return true;
            }
            else
            {
                if (_comparator(node->_value, value) == 0)
                    return true;
            }
        }
    }
    return false;
}

template <typename K, typename V>
inline std::shared_ptr<V> TreeMap<K, V>::get_value(std::shared_ptr<K> key)
{
    Node<K, V> *node = get_node(key);
    return node != nullptr ? node->_value : nullptr;
}

template <typename K, typename V>
inline std::shared_ptr<V> TreeMap<K, V>::add(std::shared_ptr<K> key, std::shared_ptr<V> value)
{
    not_null_check(key);
    if (_root == nullptr)
    {
        _root = new Node<K, V>(key, value, nullptr);
        _size++;
        after_add(_root);
        return nullptr;
    }
    Node<K, V> *node = _root, *parent = _root;
    while (node != nullptr)
    {
        parent = node;
        if (_comparator == nullptr)
        {
            if (*node->_key < *key)
                node = node->_right;
            else if (*node->_key > *key)
                node = node->_left;
            else
            {
                node->_key = key;
                std::shared_ptr<V> old = node->_value;
                node->_value = value;
                return old;
            }
        }
        else
        {
            if (_comparator(node->_key, key) < 0)
                node = node->_right;
            else if (_comparator(node->_key, key) > 0)
                node = node->_left;
            else
            {
                node->_key = key;
                std::shared_ptr<V> old = node->_value;
                node->_value = value;
                return old;
            }
        }
    }
    Node<K, V> *temp = new Node<K, V>(key, value, parent);
    if (_comparator == nullptr)
    {
        if (*parent->_key < *key)
            parent->_right = temp;
        else
            parent->_left = temp;
    }
    else
    {
        if (_comparator(parent->_key, key) < 0)
            parent->_right = temp;
        else
            parent->_left = temp;
    }
    _size++;
    after_add(temp);
    return nullptr;
}

template <typename K, typename V>
inline std::shared_ptr<V> TreeMap<K, V>::remove(std::shared_ptr<K> key)
{
    Node<K, V> *node = get_node(key);
    if (node != nullptr)
    {
        _size--;
        std::shared_ptr<V> old = node->_value;
        if (node->is_binary())
        {
            Node<K, V> *s = get_successor(node);
            node->_key = s->_key;
            node->_value = s->_value;
            node = s; //删除前驱结点
        }
        Node<K, V> *replace = node->_left != nullptr ? node->_left : node->_right;
        if (replace != nullptr)
        {
            replace->_parent = node->_parent;
            if (node->_parent == nullptr)
                _root = replace;
            else if (node == node->_parent->_left)
                node->_parent->_left = replace;
            else
                node->_parent->_right = replace;
            after_remove(replace);
        }
        else if (node->_parent != nullptr)
        {
            if (node == node->_parent->_left)
                node->_parent->_left = nullptr;
            else
                node->_parent->_right = nullptr;
            after_remove(node);
        }
        else
        {
            _root = nullptr;
        }
        delete node;
        return old;
    }
    return nullptr;
}

template <typename K, typename V>
inline void TreeMap<K, V>::inorder_traverse(Node<K, V> *node, TraverseFunc func) const
{
    if (node != nullptr)
    {
        inorder_traverse(node->_left, func);
        if (func != nullptr)
            func(node->_key);
        else
            std::cout << "<" << *node->_key << "-" << *node->_value << ">\n";
        inorder_traverse(node->_right, func);
    }
}

template <typename K, typename V>
inline void TreeMap<K, V>::clear()
{
    clear_recu(_root);
    _root = nullptr;
    _size = 0;
}

#endif /* MAP_H */
