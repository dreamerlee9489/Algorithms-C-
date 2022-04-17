#ifndef MAP_H
#define MAP_H
#include <memory>

template <typename T, typename U>
class Map
{
private:
    using TraverseFunc = bool (*)(std::shared_ptr<T> key);
    using Comparator = int (*)(std::shared_ptr<T> a, std::shared_ptr<T> b);
    static const bool BLACK = false, RED = true;
    template <typename K, typename V>
    struct Node
    {
        friend std::ostream &operator<<(std::ostream &os, const Node<K, V> &node) { return os << node.to_string(); }
        std::shared_ptr<K> _key;
        std::shared_ptr<V> _value;
        bool _color = RED;
        Node<K, V> *_parent = nullptr, *_left = nullptr, *_right = nullptr;
        Node<K, V> &operator=(const Node<K, V> &node);
        Node<K, V> &operator=(Node<K, V> &&node) noexcept;
        Node(std::shared_ptr<K> key, std::shared_ptr<K> value, Node<K, V> *parent = nullptr, Node<K, V> *left = nullptr, Node<K, V> *right = nullptr)
            : _key(key), _value(value), _parent(parent), _left(left), _right(right) {}
        Node(const Node<K, V> &node) { *this = node; }
        Node(Node<K, V> &&node) noexcept { *this = std::move(node); }
        virtual ~Node() { _key = nullptr; }
        bool is_leaf() const { return _left == nullptr && _right == nullptr; }
        bool is_binary() const { return _left != nullptr && _right != nullptr; }
        bool is_left() const { return _parent != nullptr && this == _parent->_left; }
        bool is_right() const { return _parent != nullptr && this == _parent->_right; }
        Node<K, V> *get_sibling() const;
        std::string to_string() const override { return ((IString &)*_key).to_string(); }
    };
    size_t _size = 0;
    Node<T, U> *_root = nullptr;
    Comparator _comparator = nullptr;
    void not_null_check(std::shared_ptr<T> key) const;
    Node<T, U> *get_node(std::shared_ptr<T> key) const;
    Node<T, U> *get_predecessor(Node<T, U> *node) const;
    Node<T, U> *get_successor(Node<T, U> *node) const;
    void after_add(Node<T, U> *node);
    void after_remove(Node<T, U> *node);
    void rotate_left(Node<T, U> *grand);
    void rotate_right(Node<T, U> *grand);
    void after_rotate(Node<T, U> *grand, Node<T, U> *parent, Node<T, U> *child);
    Node<T, U> *set_color(Node<T, U> *node, bool color);
    bool color_of(Node<T, U> *node) { return node == nullptr ? BLACK : ((RBNode<T> *)node)->_color; }
    bool is_black(Node<T, U> *node) { return color_of(node) == BLACK; }
    bool is_red(Node<T, U> *node) { return color_of(node) == RED; }
    void clear_recu(Node<T, U> *node);

public:
    Map(Comparator comparator = nullptr) { _comparator = comparator; }
    ~Map() { clear_recu(_root); }
    size_t size() const { return _size; }
    bool is_empty() const { return _size == 0; }
    bool contains_key(std::shared_ptr<T> key);
    bool contains_value(std::shared_ptr<U> value);
    void add(std::shared_ptr<T> key, std::shared_ptr<U> value);
    void get(std::shared_ptr<T> key);
    void remove(std::shared_ptr<T> key);
    void traverse(TraverseFunc func = nullptr) const;
    void clear();
};

template <typename T, typename U>
template <typename K, typename V>
inline Map<T, U>::Node<K, V> &Map<T, U>::Node<K, V>::operator=(const Map<T, U>::Node<K, V> &node)
{
    _key = node._key;
    _value = node._value;
    _parent = node._parent;
    _left = node._left;
    _right = node._right;
    _color = node._color;
    return *this;
}

template <typename T, typename U>
template <typename K, typename V>
inline Map<T, U>::Node<K, V> &Map<T, U>::Node<K, V>::operator=(Map<T, U>::Node<K, V> &&node)
{
    _key = std::move(node._key);
    _value = std::move(node._value);
    _parent = std::move(node._parent);
    _left = std::move(node._left);
    _right = std::move(node._right);
    _color = std::move(node._color);
    return *this;
}

template <typename T, typename U>
template <typename K, typename V>
inline Map<T, U>::Node<K, V> *Map<T, U>::Node<K, V>::get_sibling() const
{
    if (is_left())
        return _parent->_right;
    else if (is_right())
        return _parent->_left;
    return nullptr;
}

template <typename T, typename U>
inline void Map<T, U>::not_null_check(std::shared_ptr<T> key) const
{
    if (key == nullptr)
        throw std::invalid_argument("key must be not null.");
}

template <typename T, typename U>
inline Map<T, U>::Node<T, U> *Map<T, U>::get_node(std::shared_ptr<T> key) const
{

}

template <typename T, typename U>
inline Map<T, U>::Node<T, U> *Map<T, U>::get_predecessor(Map<T, U>::Node<T, U> *node) const
{

}

template <typename T, typename U>
inline Map<T, U>::Node<T, U> *Map<T, U>::get_successor(Map<T, U>::Node<T, U> *node) const
{

}

template <typename T, typename U>
inline void Map<T, U>::after_add(Map<T, U>::Node<T, U> *node)
{

}

template <typename T, typename U>
inline void Map<T, U>::after_remove(Map<T, U>::Node<T, U> *node)
{

}

template <typename T, typename U>
inline void Map<T, U>::rotate_left(Map<T, U>::Node<T, U> *grand)
{
}

template <typename T, typename U>
inline void Map<T, U>::rotate_right(Map<T, U>::Node<T, U> *grand)
{
}

template <typename T, typename U>
inline void Map<T, U>::after_rotate(Map<T, U>::Node<T, U> *grand, Map<T, U>::Node<T, U> *parent, Map<T, U>::Node<T, U> *child)
{
}

template <typename T, typename U>
inline Map<T, U>::Node<T, U> *Map<T, U>::set_color(Map<T, U>::Node<T, U> *node, bool color)
{
}

template <typename T, typename U>
inline void Map<T, U>::clear_recu(Map<T, U>::Node<T, U> *node)
{
    if (node != nullptr)
    {
        clear_recu(node->_left);
        clear_recu(node->_right);
        delete node;
    }
}

template <typename T, typename U>
inline bool Map<T, U>::contains_key(std::shared_ptr<T> key)
{

}

template <typename T, typename U>
inline bool Map<T, U>::contains_value(std::shared_ptr<U> value)
{

}

template <typename T, typename U>
inline void Map<T, U>::add(std::shared_ptr<T> key, std::shared_ptr<U> value)
{

}

template <typename T, typename U>
inline void Map<T, U>::get(std::shared_ptr<T> key)
{

}

template <typename T, typename U>
inline void Map<T, U>::remove(std::shared_ptr<T> key)
{

}

template <typename T, typename U>
inline void Map<T, U>::traverse(TraverseFunc func) const
{

}

template <typename T, typename U>
inline void Map<T, U>::clear()
{
    clear_recu(_root);
    _root = nullptr;
    _size = 0;
}

#endif /* MAP_H */
