#ifndef LINKED_HASH_MAP_H
#define LINKED_HASH_MAP_H
#include "./15_HashMap.h"
/**
 * @brief 按元素添加顺序遍历的哈希映射
 * @date 2022-04-21
 * @tparam K 键必须继承IHashable
 * @tparam V
 */
template <typename K, typename V>
class LinkedHashMap : public HashMap<K, V>
{
    using NODE = typename HashMap<K, V>::template Node<K, V>;
    template <typename _K, typename _V>
    struct LinkedNode : public NODE
    {
        LinkedNode<_K, _V> *_prev = nullptr, *_next = nullptr;
        LinkedNode(std::shared_ptr<_K> key, std::shared_ptr<_V> value, NODE *parent = nullptr)
            : NODE(key, value, parent, nullptr, nullptr) {}
        ~LinkedNode() = default;
    };
    LinkedNode<K, V> *_head = nullptr, *_tail = nullptr;
    LinkedNode<K, V> *create_node(std::shared_ptr<K> key, std::shared_ptr<V> value, NODE *parent) override;
    void after_remove_derived(NODE *willnode, NODE *rmvnode) override;

public:
    LinkedHashMap(typename HashMap<K, V>::Comparator comparator = nullptr) : HashMap<K, V>(comparator) { }
    ~LinkedHashMap() = default;
    bool contains_value(std::shared_ptr<V> value) const override;
    void traverse(typename HashMap<K, V>::TraverseFunc func = nullptr) const override;
    void clear() override;
};

template <typename K, typename V>
inline LinkedHashMap<K, V>::LinkedNode<K, V> *LinkedHashMap<K, V>::create_node(std::shared_ptr<K> key, std::shared_ptr<V> value, NODE *parent)
{
    LinkedNode<K, V> *node = new LinkedNode<K, V>(key, value, parent);
    if (_head == nullptr)
        _head = _tail = node;
    else
    {
        _tail->_next = node;
        node->_prev = _tail;
        _tail = node;
    }
    return node;
}

template <typename K, typename V>
inline void LinkedHashMap<K, V>::after_remove_derived(NODE *willnode, NODE *rmvnode)
{
    LinkedNode<K, V> *node1 = (LinkedNode<K, V> *)willnode;
    LinkedNode<K, V> *node2 = (LinkedNode<K, V> *)rmvnode;
    if (node1 != node2)
    {
        LinkedNode<K, V> *temp = node1->_prev;
        node1->_prev = node2->_prev;
        node2->_prev = temp;
        if (node1->_prev == nullptr)
            _head = node1;
        else
            node1->_prev->_next = node1;
        if (node2->_prev == nullptr)
            _head = node2;
        else
            node2->_prev->_next = node2;
        temp = node1->_next;
        node1->_next = node2->_next;
        node2->_next = temp;
        if (node1->_next == nullptr)
            _tail = node1;
        else
            node1->_next->_prev = node1;
        if (node2->_next == nullptr)
            _tail = node2;
        else
            node2->_next->_prev = node2;
    }
    LinkedNode<K, V> *prev = node2->_prev;
    LinkedNode<K, V> *next = node2->_next;
    if (prev == nullptr)
        _head = next;
    else
        prev->_next = next;
    if (next == nullptr)
        _tail = prev;
    else
        next->_prev = prev;
    delete node2;
}

template <typename K, typename V>
inline bool LinkedHashMap<K, V>::contains_value(std::shared_ptr<V> value) const
{
    LinkedNode<K, V> *node = _head;
    while (node != nullptr)
    {
        if (*value == *node->_value)
            return true;
        node = node->_next;
    }
    return false;
}

template <typename K, typename V>
inline void LinkedHashMap<K, V>::traverse(typename HashMap<K, V>::TraverseFunc func) const
{
    LinkedNode<K, V> *node = _head;
    while (node != nullptr)
    {
        if (func != nullptr)
            func(node->_key, node->_value);
        else
            std::cout << *node << "\n";
        node = node->_next;
    }
}

template <typename K, typename V>
inline void LinkedHashMap<K, V>::clear()
{
    HashMap<K, V>::clear();
    _head = nullptr;
    _tail = nullptr;
}

#endif /* LINKED_HASH_MAP_H */