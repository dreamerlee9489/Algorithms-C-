#ifndef HASH_MAP_H
#define HASH_MAP_H
#include "./12_IMap.h"
#include "./IHashable.h"

template <typename K, typename V>
class HashMap : public IMap<K, V>
{
    static const bool BLACK = false, RED = true;
    static const size_t DEFAULT_CAPACITY = 16;
    template <typename _K, typename _V>
    struct Node 
    {
        friend std::ostream &operator<<(std::ostream &os, const Node<_K, _V> &node) { return os << *node->_key << "-" << *node->_value; }
        int _hash = 0;
        bool _color = RED;
        std::shared_ptr<_K> _key = nullptr;
        std::shared_ptr<_V> _value = nullptr;
        Node<_K, _V> *_parent = nullptr, *_left = nullptr, *_right = nullptr;
        Node<_K, _V> &operator=(const Node<_K, _V> &node);
        Node<_K, _V> &operator=(Node<_K, _V> &&node) noexcept;
        Node() = default;
        Node(std::shared_ptr<_K> key, std::shared_ptr<_V> value, Node<_K, _V> *parent = nullptr, Node<_K, _V> *left = nullptr, Node<_K, _V> *right = nullptr)
            : _key(key), _value(value), _parent(parent), _left(left), _right(right) { _hash = _key == nullptr ? 0 : ((IHashable&)*_key).hash_code(); }
        Node(const Node<_K, _V> &node) { *this = node; }
        Node(Node<_K, _V> &&node) noexcept { *this = std::move(node); }
        virtual ~Node();
        bool is_leaf() const { return _left == nullptr && _right == nullptr; }
        bool is_binary() const { return _left != nullptr && _right != nullptr; }
        bool is_left() const { return _parent != nullptr && this == _parent->_left; }
        bool is_right() const { return _parent != nullptr && this == _parent->_right; }
        Node<_K, _V> *get_sibling() const;
    };
    size_t _size = 0, _capacity = DEFAULT_CAPACITY;
    Node<K, V> **_table = nullptr;
    typename IMap<K, V>::Comparator _comparator = nullptr;
    Node<K, V> *get_node(Node<K, V> *node, std::shared_ptr<K> key) const;
    Node<K, V> *get_successor(Node<K, V> *node) const;
    int get_index(Node<K, V> *node);
    void rotate_left(Node<K, V> *grand);
    void rotate_right(Node<K, V> *grand);
    void after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child);
    Node<K, V> *set_color(Node<K, V> *node, bool color);
    bool color_of(Node<K, V> *node) { return node == nullptr ? BLACK : node->_color; }
    bool is_black(Node<K, V> *node) { return color_of(node) == BLACK; }
    bool is_red(Node<K, V> *node) { return color_of(node) == RED; }
    void clear_recu(Node<K, V> *root);

public:
    HashMap(typename IMap<K, V>::Comparator comparator = nullptr);
    ~HashMap();
    size_t size() const override { return _size; }
    bool is_empty() const override { return _size == 0; }
    bool contains_key(std::shared_ptr<K> key) override;
    bool contains_value(std::shared_ptr<V> value) override;
    std::shared_ptr<V> get_value(std::shared_ptr<K> key) override;
    std::shared_ptr<V> add(std::shared_ptr<K> key, std::shared_ptr<V> value) override;
    std::shared_ptr<V> remove(std::shared_ptr<K> key) override;
    void traverse(typename IMap<K, V>::TraverseFunc func = nullptr) const override;
    void clear() override;
};

template <typename K, typename V>
template <typename _K, typename _V>
inline HashMap<K, V>::Node<_K, _V> &HashMap<K, V>::Node<_K, _V>::operator=(const Node<_K, _V> &node)
{
    _key = node._key;
    _value = node._value;
    _parent = node._parent;
    _left = node._left;
    _right = node._right;
    _color = node._color;
    _hash = node._hash;
    return *this;
}

template <typename K, typename V>
template <typename _K, typename _V>
inline HashMap<K, V>::Node<_K, _V> &HashMap<K, V>::Node<_K, _V>::operator=(Node<_K, _V> &&node) noexcept
{
    _key = nullptr;
    _value = nullptr;
    this = &node;
    return *this;
}

template <typename K, typename V>
template <typename _K, typename _V>
inline HashMap<K, V>::Node<_K, _V>::~Node()
{
    _key = nullptr;
    _value = nullptr;
}

template <typename K, typename V>
template <typename _K, typename _V>
inline HashMap<K, V>::Node<_K, _V> *HashMap<K, V>::Node<_K, _V>::get_sibling() const
{
    if (is_left())
        return _parent->_right;
    else if (is_right())
        return _parent->_left;
    return nullptr;
}

template <typename K, typename V>
inline HashMap<K, V>::Node<K, V> *HashMap<K, V>::get_node(Node<K, V> *node, std::shared_ptr<K> key) const
{
    return nullptr;
}

template <typename K, typename V>
inline HashMap<K, V>::Node<K, V> *HashMap<K, V>::get_successor(Node<K, V> *node) const
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
inline HashMap<K, V>::HashMap(typename IMap<K, V>::Comparator comparator)
{
    _comparator = comparator;
    _table = new Node<K, V>*[DEFAULT_CAPACITY];
}

template <typename K, typename V>
inline HashMap<K, V>::~HashMap()
{
    //delete[] _table;
}

template <typename K, typename V>
bool HashMap<K, V>::contains_key(std::shared_ptr<K> key) 
{ 
    return false; 
}

template <typename K, typename V>
bool HashMap<K, V>::contains_value(std::shared_ptr<V> value) 
{ 
    return false; 
}

template <typename K, typename V>
std::shared_ptr<V> HashMap<K, V>::get_value(std::shared_ptr<K> key)
{
    return nullptr;
}

template <typename K, typename V>
std::shared_ptr<V> HashMap<K, V>::add(std::shared_ptr<K> key, std::shared_ptr<V> value)
{
    return nullptr;
}

template <typename K, typename V>
std::shared_ptr<V> HashMap<K, V>::remove(std::shared_ptr<K> key)
{
    return nullptr;
}

template <typename K, typename V>
void HashMap<K, V>::traverse(typename IMap<K, V>::TraverseFunc func) const
{
}

template <typename K, typename V>
inline void HashMap<K, V>::clear()
{
    if(_size == 0)
        return;
    _size = 0;
    for(size_t i = 0; i < _capacity; ++i)
        clear_recu(_table[i]);
}

template <typename K, typename V>
int HashMap<K, V>::get_index(Node<K, V> *node)
{
    return 0;
}

template <typename K, typename V>
inline void HashMap<K, V>::rotate_left(Node<K, V> *grand)
{
    Node<K, V> *parent = grand->_right;
    Node<K, V> *child = parent->_left;
    grand->_right = child;
    parent->_left = grand;
    after_rotate(grand, parent, child);
}

template <typename K, typename V>
inline void HashMap<K, V>::rotate_right(Node<K, V> *grand)
{
    Node<K, V> *parent = grand->_left;
    Node<K, V> *child = parent->_right;
    grand->_left = child;
    parent->_right = grand;
    after_rotate(grand, parent, child);
}

template <typename K, typename V>
inline void HashMap<K, V>::after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child)
{
    parent->_parent = grand->_parent;
    if (grand->is_left())
        grand->_parent->_left = parent;
    else if (grand->is_right())
        grand->_parent->_right = parent;
    else
        _table[get_index(grand)] = parent;
    if (child != nullptr)
        child->_parent = grand;
    grand->_parent = parent;
}

template <typename K, typename V>
inline HashMap<K, V>::Node<K, V> *HashMap<K, V>::set_color(Node<K, V> *node, bool color)
{
    if (node != nullptr)
        node->_color = color;
    return node;
}

template <typename K, typename V>
inline void HashMap<K, V>::clear_recu(Node<K, V> *root)
{
    if (root != nullptr)
    {
        clear_recu(root->_left);
        clear_recu(root->_right);
        delete root;
    }
}

#endif /* HASH_MAP_H */
