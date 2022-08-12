#ifndef LINKED_HASH_MAP_HPP
#define LINKED_HASH_MAP_HPP

#include "./15_HashMap.hpp"

namespace app {
    /**
     * @brief 按元素添加顺序遍历的哈希映射
     * @date 2022-04-21
     * @tparam K
     * @tparam V
     */
    template<typename K, typename V>
    class LinkedHashMap : public HashMap<K, V> {
        using NODE = typename HashMap<K, V>::template Node<K, V>;

        template<typename _K, typename _V>
        struct LinkedNode : public NODE {
            LinkedNode<_K, _V> *pPrev = nullptr, *pNext = nullptr;

            LinkedNode &operator=(const LinkedNode<_K, _V> &node);

            LinkedNode &operator=(LinkedNode<_K, _V> &&node) noexcept;

            LinkedNode(shared_ptr<_K> key, shared_ptr<_V> value, NODE *parent = nullptr)
                    : NODE(key, value, parent, nullptr, nullptr) {}

            LinkedNode(const LinkedNode<_K, _V> &node) { *this = node; }

            LinkedNode(LinkedNode<_K, _V> &&node) noexcept { *this = move(node); }

            ~LinkedNode() = default;
        };

        LinkedNode<K, V> *_head = nullptr, *_tail = nullptr;

        LinkedNode<K, V> *create_node(shared_ptr<K> key, shared_ptr<V> value, NODE *parent) override;

        void after_remove_derived(NODE *willnode, NODE *rmvnode) override;

    public:
        LinkedHashMap<K, V> &operator=(const LinkedHashMap<K, V> &map);

        LinkedHashMap<K, V> &operator=(LinkedHashMap<K, V> &&map) noexcept;

        LinkedHashMap(typename HashMap<K, V>::Comparator comparator = nullptr) : HashMap<K, V>(comparator) {}

        LinkedHashMap(const LinkedHashMap<K, V> &map) { *this = map; }

        LinkedHashMap(LinkedHashMap<K, V> &&map) noexcept { *this = move(map); }

        ~LinkedHashMap() = default;

        bool containsmValue(shared_ptr<V> value) const override;

        void traverse(typename HashMap<K, V>::TraverseFunc func = nullptr) const override;

        void clear() override {
            HashMap<K, V>::clear();
            _head = nullptr;
            _tail = nullptr;
        }
    };

    template<typename K, typename V>
    template<typename _K, typename _V>
    inline LinkedHashMap<K, V>::LinkedNode<_K, _V> &
    LinkedHashMap<K, V>::LinkedNode<_K, _V>::operator=(const LinkedNode<_K, _V> &node) {
        this->pKey = node.pKey;
        this->mValue = node.mValue;
        this->pParent = node.pParent;
        this->pLeft = node.pLeft;
        this->pRight = node.pRight;
        pPrev = node.pPrev;
        pNext = node.pNext;
        return *this;
    }

    template<typename K, typename V>
    template<typename _K, typename _V>
    inline LinkedHashMap<K, V>::LinkedNode<_K, _V> &
    LinkedHashMap<K, V>::LinkedNode<_K, _V>::operator=(LinkedNode<_K, _V> &&node) noexcept {
        this->pKey = nullptr;
        this->mValue = nullptr;
        this = &node;
        return *this;
    }

    template<typename K, typename V>
    inline LinkedHashMap<K, V>::LinkedNode<K, V> *
    LinkedHashMap<K, V>::create_node(shared_ptr<K> key, shared_ptr<V> value, NODE *parent) {
        LinkedNode<K, V> *node = new LinkedNode<K, V>(key, value, parent);
        if (_head == nullptr)
            _head = _tail = node;
        else {
            _tail->pNext = node;
            node->pPrev = _tail;
            _tail = node;
        }
        return node;
    }

    template<typename K, typename V>
    inline void LinkedHashMap<K, V>::after_remove_derived(NODE *willnode, NODE *rmvnode) {
        LinkedNode<K, V> *node1 = (LinkedNode<K, V> *) willnode;
        LinkedNode<K, V> *node2 = (LinkedNode<K, V> *) rmvnode;
        if (node1 != node2) {
            LinkedNode<K, V> *temp = node1->pPrev;
            node1->pPrev = node2->pPrev;
            node2->pPrev = temp;
            if (node1->pPrev == nullptr)
                _head = node1;
            else
                node1->pPrev->pNext = node1;
            if (node2->pPrev == nullptr)
                _head = node2;
            else
                node2->pPrev->pNext = node2;
            temp = node1->pNext;
            node1->pNext = node2->pNext;
            node2->pNext = temp;
            if (node1->pNext == nullptr)
                _tail = node1;
            else
                node1->pNext->pPrev = node1;
            if (node2->pNext == nullptr)
                _tail = node2;
            else
                node2->pNext->pPrev = node2;
        }
        LinkedNode<K, V> *prev = node2->pPrev;
        LinkedNode<K, V> *next = node2->pNext;
        if (prev == nullptr)
            _head = next;
        else
            prev->pNext = next;
        if (next == nullptr)
            _tail = prev;
        else
            next->pPrev = prev;
        delete node2;
    }

    template<typename K, typename V>
    inline LinkedHashMap<K, V> &LinkedHashMap<K, V>::operator=(const LinkedHashMap<K, V> &map) {
        clear();
        delete[] this->_table;
        this->_table = nullptr;
        if (map.mSize > 0) {
            this->mCapacity = map.mCapacity;
            this->_table = new NODE *[this->mCapacity];
            this->mComparator = map.mComparator;
            for (size_t i = 0; i < this->mCapacity; ++i)
                this->_table[i] = nullptr;
            LinkedNode<K, V> *node = map._head;
            while (node != nullptr) {
                this->add(node->pKey, node->mValue);
                node = node->pNext;
            }
        }
        return *this;
    }

    template<typename K, typename V>
    inline LinkedHashMap<K, V> &LinkedHashMap<K, V>::operator=(LinkedHashMap<K, V> &&map) noexcept {
        clear();
        this->mSize = map.mSize;
        this->mCapacity = map.mCapacity;
        this->mComparator = map.mComparator;
        this->_table = map._table;
        _head = map._head;
        _tail = map._tail;
        map.mSize = 0;
        map.mComparator = nullptr;
        map._table = nullptr;
        map._head = map._tail = nullptr;
        return *this;
    }

    template<typename K, typename V>
    inline bool LinkedHashMap<K, V>::containsmValue(shared_ptr<V> value) const {
        LinkedNode<K, V> *node = _head;
        while (node != nullptr) {
            if (*value == *node->mValue)
                return true;
            node = node->pNext;
        }
        return false;
    }

    template<typename K, typename V>
    inline void LinkedHashMap<K, V>::traverse(typename HashMap<K, V>::TraverseFunc func) const {
        LinkedNode<K, V> *node = _head;
        while (node != nullptr) {
            if (func != nullptr)
                func(node->pKey, node->mValue);
            else
                cout << *node << "\n";
            node = node->pNext;
        }
    }
} // namespace app

#endif /* LINKED_HASH_MAP_HPP */