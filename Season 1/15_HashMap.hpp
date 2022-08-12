#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include "./14_IMap.hpp"

namespace app {
    /**
     * @brief 哈希映射
     * @date 2022-04-20
     * @tparam K
     * @tparam V
     */
    template<typename K, typename V>
    class HashMap : public IMap<K, V> {
    protected:
        static const bool BLACK = false, RED = true;
        static const size_t DEFAULT_CAPACITY = 16;
        static constexpr double LOAD_FACTOR = 0.75;

        template<typename _K, typename _V>
        struct Node {
            friend ostream &operator<<(ostream &os, const Node &node) {
                return os << "<" << *node.pKey << "-" << *node.mValue << ">";
            }

            size_t _hash = 0;
            bool mColor = RED;
            shared_ptr<_K> pKey = nullptr;
            shared_ptr<_V> mValue = nullptr;
            Node<_K, _V> *pParent = nullptr, *pLeft = nullptr, *pRight = nullptr;

            Node<_K, _V> &operator=(const Node<_K, _V> &node);

            Node<_K, _V> &operator=(Node<_K, _V> &&node) noexcept;

            Node(shared_ptr<_K> key, shared_ptr<_V> value, Node<_K, _V> *parent = nullptr, Node<_K, _V> *left = nullptr,
                 Node<_K, _V> *right = nullptr)
                    : pKey(key), mValue(value), pParent(parent), pLeft(left), pRight(right) {
                _hash = pKey == nullptr ? 0 : hash<_K>()(*key);
            }

            Node(const Node<_K, _V> &node) { *this = node; }

            Node(Node<_K, _V> &&node) noexcept { *this = move(node); }

            virtual ~Node() {
                pKey = nullptr;
                mValue = nullptr;
            }

            bool is_leaf() const { return pLeft == nullptr && pRight == nullptr; }

            bool is_binary() const { return pLeft != nullptr && pRight != nullptr; }

            bool ispLeft() const { return pParent != nullptr && this == pParent->pLeft; }

            bool ispRight() const { return pParent != nullptr && this == pParent->pRight; }

            Node<_K, _V> *get_sibling() const;
        };

        size_t mSize = 0, mCapacity = DEFAULT_CAPACITY;
        Node<K, V> **_table = nullptr;
        typename IMap<K, V>::Comparator mComparator = nullptr;

        Node<K, V> *get_node(shared_ptr<K> key) const {
            Node<K, V> *root = _table[get_index(key)];
            return root == nullptr ? nullptr : get_node(root, key);
        }

        Node<K, V> *get_node(Node<K, V> *node, shared_ptr<K> key1) const;

        Node<K, V> *get_successor(Node<K, V> *node) const;

        int get_index(Node<K, V> *node) const { return node->_hash & (mCapacity - 1); }

        int get_index(shared_ptr<K> key) const { return get_hash(key) & (mCapacity - 1); } // 哈希值位与容量映射到哈希数组
        size_t get_hash(shared_ptr<K> key) const {
            if (key != nullptr)
                return hash<K>()(*key);
            return 0;
        }

        void ensuremCapacity();

        void move_node(Node<K, V> *newnode);

        void after_add(Node<K, V> *node);

        void after_remove(Node<K, V> *node);

        void rotatepLeft(Node<K, V> *grand);

        void rotatepRight(Node<K, V> *grand);

        void after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child);

        Node<K, V> *setmColor(Node<K, V> *node, bool color);

        bool color_of(Node<K, V> *node) const { return node == nullptr ? BLACK : node->mColor; }

        bool is_black(Node<K, V> *node) const { return color_of(node) == BLACK; }

        bool is_red(Node<K, V> *node) const { return color_of(node) == RED; }

        void clear_recu(Node<K, V> *root);

        virtual Node<K, V> *create_node(shared_ptr<K> key, shared_ptr<V> value, Node<K, V> *parent) {
            return new Node<K, V>(key, value, parent);
        }

        virtual void after_remove_derived(Node<K, V> *willnode, Node<K, V> *rmvnode) { delete rmvnode; }

    public:
        HashMap<K, V> &operator=(const HashMap<K, V> &map);

        HashMap<K, V> &operator=(HashMap<K, V> &&map) noexcept;

        HashMap(typename IMap<K, V>::Comparator comparator = nullptr) {
            mComparator = comparator;
            _table = new Node<K, V> *[DEFAULT_CAPACITY];
            for (size_t i = 0; i < mCapacity; ++i)
                _table[i] = nullptr;
        }

        virtual ~HashMap() {
            clear();
            delete[] _table;
        }

        HashMap(const HashMap<K, V> &map) { *this = map; }

        HashMap(HashMap<K, V> &&map) noexcept { *this = move(map); }

        size_t size() const override { return mSize; }

        size_t capacity() const { return mCapacity; }

        bool is_empty() const override { return mSize == 0; }

        bool containspKey(shared_ptr<K> key) const override { return get_node(key) != nullptr; }

        bool containsmValue(shared_ptr<V> value) const override;

        shared_ptr<V> getmValue(shared_ptr<K> key) const override {
            Node<K, V> *node = get_node(key);
            return node != nullptr ? node->mValue : nullptr;
        }

        shared_ptr<V> add(shared_ptr<K> key, shared_ptr<V> value) override;

        shared_ptr<V> remove(shared_ptr<K> key) override;

        virtual void traverse(typename IMap<K, V>::TraverseFunc func = nullptr) const;

        void clear() override {
            if (mSize > 0) {
                mSize = 0;
                for (size_t i = 0; i < mCapacity; ++i)
                    clear_recu(_table[i]);
            }
        }
    };

    template<typename K, typename V>
    template<typename _K, typename _V>
    inline HashMap<K, V>::Node<_K, _V> &HashMap<K, V>::Node<_K, _V>::operator=(const Node<_K, _V> &node) {
        pKey = node.pKey;
        mValue = node.mValue;
        pParent = node.pParent;
        pLeft = node.pLeft;
        pRight = node.pRight;
        mColor = node.mColor;
        _hash = node._hash;
        return *this;
    }

    template<typename K, typename V>
    template<typename _K, typename _V>
    inline HashMap<K, V>::Node<_K, _V> &HashMap<K, V>::Node<_K, _V>::operator=(Node<_K, _V> &&node) noexcept {
        pKey = nullptr;
        mValue = nullptr;
        this = &node;
        return *this;
    }

    template<typename K, typename V>
    template<typename _K, typename _V>
    inline HashMap<K, V>::Node<_K, _V> *HashMap<K, V>::Node<_K, _V>::get_sibling() const {
        if (ispLeft())
            return pParent->pRight;
        else if (ispRight())
            return pParent->pLeft;
        return nullptr;
    }

    template<typename K, typename V>
    inline HashMap<K, V> &HashMap<K, V>::operator=(const HashMap<K, V> &map) {
        clear();
        delete[] _table;
        mCapacity = DEFAULT_CAPACITY;
        _table = new Node<K, V> *[mCapacity];
        mComparator = map.mComparator;
        for (size_t i = 0; i < mCapacity; ++i)
            _table[i] = nullptr;
        if (map.mSize > 0) {
            queue<Node<K, V> *> q;
            for (size_t i = 0; i < map.mCapacity; ++i) {
                if (map._table[i] != nullptr) {
                    q.push(map._table[i]);
                    while (!q.empty()) {
                        Node<K, V> *node = q.front();
                        add(node->pKey, node->mValue);
                        q.pop();
                        if (node->pLeft != nullptr)
                            q.push(node->pLeft);
                        if (node->pRight != nullptr)
                            q.push(node->pRight);
                    }
                }
            }
        }
        return *this;
    }

    template<typename K, typename V>
    inline HashMap<K, V> &HashMap<K, V>::operator=(HashMap<K, V> &&map) noexcept {
        clear();
        mSize = map.mSize;
        mCapacity = map.mCapacity;
        mComparator = map.mComparator;
        _table = map._table;
        map.mSize = 0;
        map.mComparator = nullptr;
        map._table = nullptr;
        return *this;
    }

    template<typename K, typename V>
    inline bool HashMap<K, V>::containsmValue(shared_ptr<V> value) const {
        if (mSize != 0) {
            queue<Node<K, V> *> q;
            for (size_t i = 0; i < mCapacity; ++i) {
                if (_table[i] != nullptr) {
                    q.push(_table[i]);
                    while (!q.empty()) {
                        Node<K, V> *node = q.front();
                        q.pop();
                        if (*value == *node->mValue)
                            return true;
                        if (node->pLeft != nullptr)
                            q.push(node->pLeft);
                        if (node->pRight != nullptr)
                            q.push(node->pRight);
                    }
                }
            }
        }
        return false;
    }

    template<typename K, typename V>
    inline shared_ptr<V> HashMap<K, V>::add(shared_ptr<K> key, shared_ptr<V> value) {
        ensuremCapacity();
        int index = get_index(key);
        Node<K, V> *root = _table[index];
        if (root == nullptr) {
            root = this->create_node(key, value, nullptr);
            _table[index] = root;
            mSize++;
            after_add(root);
            return nullptr;
        }
        Node<K, V> *parent = root, *node = root;
        int cmp = 0;
        shared_ptr<K> key1 = key;
        size_t hash1 = get_hash(key1);
        Node<K, V> *result = nullptr;
        bool scanned = false;
        while (node != nullptr) {
            parent = node;
            shared_ptr<K> key2 = node->pKey;
            size_t hash2 = node->_hash;
            if (hash1 > hash2)
                cmp = 1;
            else if (hash1 < hash2)
                cmp = -1;
            else if (*key1 == *key2)
                cmp = 0;
            else if (key1 != nullptr && key2 != nullptr && mComparator != nullptr && typeid(*key1) == typeid(*key2) &&
                     (cmp = mComparator(key1, key2)) != 0) {
            } else if (scanned)
                cmp = key1.get() - key2.get();
            else {
                if (node->pLeft != nullptr && (result = get_node(node->pLeft, key1)) != nullptr ||
                    (node->pRight != nullptr && (result = get_node(node->pRight, key1)) != nullptr)) {
                    node = result;
                    cmp = 0;
                } else {
                    scanned = true;
                    cmp = key1.get() - key2.get();
                }
            }
            if (cmp > 0)
                node = node->pRight;
            else if (cmp < 0)
                node = node->pLeft;
            else {
                shared_ptr<V> old = node->mValue;
                node->pKey = key;
                node->mValue = value;
                node->_hash = hash1;
                return old;
            }
        }
        Node<K, V> *newnode = this->create_node(key, value, parent);
        if (cmp > 0)
            parent->pRight = newnode;
        else
            parent->pLeft = newnode;
        mSize++;
        after_add(newnode);
        return nullptr;
    }

    template<typename K, typename V>
    inline shared_ptr<V> HashMap<K, V>::remove(shared_ptr<K> key) {
        Node<K, V> *node = get_node(key);
        if (node != nullptr) {
            mSize--;
            Node<K, V> *willnode = node;
            shared_ptr<V> old = node->mValue;
            if (node->is_binary()) {
                Node<K, V> *s = get_successor(node);
                node->pKey = s->pKey;
                node->mValue = s->mValue;
                node->_hash = s->_hash;
                node = s;
            }
            Node<K, V> *replace = node->pLeft != nullptr ? node->pLeft : node->pRight;
            int index = get_index(node);
            if (replace != nullptr) {
                replace->pParent = node->pParent;
                if (node->pParent == nullptr)
                    _table[index] = replace;
                else if (node == node->pParent->pLeft)
                    node->pParent->pLeft = replace;
                else
                    node->pParent->pRight = replace;
                after_remove(replace);
            } else if (node->pParent != nullptr) {
                if (node == node->pParent->pLeft)
                    node->pParent->pLeft = nullptr;
                else
                    node->pParent->pRight = nullptr;
                after_remove(node);
            } else {
                _table[index] = nullptr;
            }
            this->after_remove_derived(willnode, node);
            return old;
        }
        return nullptr;
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::traverse(typename IMap<K, V>::TraverseFunc func) const {
        if (mSize > 0) {
            queue<Node<K, V> *> q;
            for (size_t i = 0; i < mCapacity; ++i) {
                if (_table[i] != nullptr) {
                    cout << "---------- " << i << " ----------\n";
                    q.push(_table[i]);
                    size_t lv_cnt = 1;
                    while (!q.empty()) {
                        Node<K, V> *node = q.front();
                        q.pop();
                        lv_cnt--;
                        if (node->pLeft != nullptr)
                            q.push(node->pLeft);
                        if (node->pRight != nullptr)
                            q.push(node->pRight);
                        if (func != nullptr)
                            func(node->pKey, node->mValue);
                        else
                            cout << *node << "\t";
                        if (lv_cnt == 0) {
                            lv_cnt = q.size();
                            cout << "\n";
                        }
                    }
                }
            }
        }
    }

    template<typename K, typename V>
    inline HashMap<K, V>::Node<K, V> *HashMap<K, V>::get_node(Node<K, V> *node, shared_ptr<K> key1) const {
        size_t hash1 = get_hash(key1);
        Node<K, V> *result = nullptr;
        int cmp = 0;
        while (node != nullptr) {
            shared_ptr<K> key2 = node->pKey;
            size_t hash2 = node->_hash;
            if (hash1 > hash2)
                node = node->pRight;
            else if (hash1 < hash2)
                node = node->pLeft;
            else if (*key1 == *key2)
                return node;
            else if (key1 != nullptr && key2 != nullptr && mComparator != nullptr && typeid(*key1) == typeid(*key2) &&
                     (cmp = mComparator(key1, key2)) != 0)
                node = cmp > 0 ? node->pRight : node->pLeft;
            else if (node->pRight != nullptr && (result = get_node(node->pRight, key1)) != nullptr)
                return result;
            else
                node = node->pLeft;
        }
        return nullptr;
    }

    template<typename K, typename V>
    inline HashMap<K, V>::Node<K, V> *HashMap<K, V>::get_successor(Node<K, V> *node) const {
        if (node != nullptr) {
            Node<K, V> *p = node->pRight;
            if (p != nullptr) {
                while (p->pLeft != nullptr)
                    p = p->pLeft;
                return p;
            }
            while (node->pParent != nullptr && node == node->pParent->pRight)
                node = node->pParent;
            return node->pParent;
        }
        return nullptr;
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::ensuremCapacity() {
        if (mSize * 1.0 / mCapacity * 1.0 > LOAD_FACTOR) {
            Node<K, V> **old = _table;
            _table = new Node<K, V> *[mCapacity << 1];
            for (size_t i = 0; i < mCapacity << 1; ++i)
                _table[i] = nullptr;
            queue<Node<K, V> *> q;
            for (size_t i = 0; i < mCapacity; ++i) {
                if (old[i] != nullptr) {
                    q.push(old[i]);
                    while (!q.empty()) {
                        Node<K, V> *node = q.front();
                        q.pop();
                        if (node->pLeft != nullptr)
                            q.push(node->pLeft);
                        if (node->pRight != nullptr)
                            q.push(node->pRight);
                        move_node(node);
                    }
                }
            }
            mCapacity <<= 1;
            delete[] old;
        }
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::move_node(Node<K, V> *newnode) {
        newnode->pParent = nullptr;
        newnode->pLeft = nullptr;
        newnode->pRight = nullptr;
        newnode->mColor = RED;
        int index = get_index(newnode);
        Node<K, V> *root = _table[index];
        if (root == nullptr) {
            root = newnode;
            _table[index] = root;
            after_add(root);
            return;
        }
        Node<K, V> *parent = root, *node = root;
        int cmp = 0;
        shared_ptr<K> key1 = newnode->pKey;
        size_t hash1 = newnode->_hash;
        while (node != nullptr) {
            parent = node;
            shared_ptr<K> key2 = node->pKey;
            size_t hash2 = node->_hash;
            if (hash1 > hash2)
                cmp = 1;
            else if (hash1 < hash2)
                cmp = -1;
            else if (key1 != nullptr && key2 != nullptr && mComparator != nullptr && typeid(*key1) == typeid(*key2) &&
                     (cmp = mComparator(key1, key2)) != 0) {
            } else
                cmp = key1.get() - key2.get();

            if (cmp > 0)
                node = node->pRight;
            else if (cmp < 0)
                node = node->pLeft;
        }
        newnode->pParent = parent;
        if (cmp > 0)
            parent->pRight = newnode;
        else
            parent->pLeft = newnode;
        after_add(newnode);
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::after_add(Node<K, V> *node) {
        Node<K, V> *parent = node->pParent;
        if (parent == nullptr) {
            setmColor(node, BLACK);
            return;
        }
        if (is_red(parent)) {
            Node<K, V> *uncle = parent->get_sibling();
            Node<K, V> *grand = setmColor(parent->pParent, RED);
            if (is_red(uncle)) {
                setmColor(parent, BLACK);
                setmColor(uncle, BLACK);
                after_add(grand);
                return;
            }
            if (parent->ispLeft()) {
                if (node->ispLeft())
                    setmColor(parent, BLACK);
                else {
                    setmColor(node, BLACK);
                    rotatepLeft(parent);
                }
                rotatepRight(grand);
            } else {
                if (node->ispLeft()) {
                    setmColor(node, BLACK);
                    rotatepRight(parent);
                } else
                    setmColor(parent, BLACK);
                rotatepLeft(grand);
            }
        }
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::after_remove(Node<K, V> *node) {
        if (is_red(node)) {
            setmColor(node, BLACK);
            return;
        }
        Node<K, V> *parent = node->pParent;
        if (parent != nullptr) {
            bool ispLeft = parent->pLeft == nullptr || node->ispLeft();
            Node<K, V> *sibling = ispLeft ? parent->pRight : parent->pLeft;
            if (ispLeft) {
                if (is_red(sibling)) {
                    setmColor(sibling, BLACK);
                    setmColor(parent, RED);
                    rotatepLeft(parent);
                    sibling = parent->pRight;
                }
                if (is_black(sibling->pLeft) && is_black(sibling->pRight)) {
                    bool parent_black = is_black(parent);
                    setmColor(parent, BLACK);
                    setmColor(sibling, RED);
                    if (parent_black)
                        after_remove(parent);
                } else {
                    if (is_black(sibling->pRight)) {
                        rotatepRight(sibling);
                        sibling = parent->pRight;
                    }
                    setmColor(sibling, color_of(parent));
                    setmColor(sibling->pRight, BLACK);
                    setmColor(parent, BLACK);
                    rotatepLeft(parent);
                }
            } else {
                if (is_red(sibling)) {
                    setmColor(sibling, BLACK);
                    setmColor(parent, RED);
                    rotatepRight(parent);
                    sibling = parent->pLeft;
                }
                if (is_black(sibling->pLeft) && is_black(sibling->pRight)) {
                    bool parent_black = is_black(parent);
                    setmColor(parent, BLACK);
                    setmColor(sibling, RED);
                    if (parent_black)
                        after_remove(parent);
                } else {
                    if (is_black(sibling->pLeft)) {
                        rotatepLeft(sibling);
                        sibling = parent->pLeft;
                    }
                    setmColor(sibling, color_of(parent));
                    setmColor(sibling->pLeft, BLACK);
                    setmColor(parent, BLACK);
                    rotatepRight(parent);
                }
            }
        }
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::rotatepLeft(Node<K, V> *grand) {
        Node<K, V> *parent = grand->pRight;
        Node<K, V> *child = parent->pLeft;
        grand->pRight = child;
        parent->pLeft = grand;
        after_rotate(grand, parent, child);
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::rotatepRight(Node<K, V> *grand) {
        Node<K, V> *parent = grand->pLeft;
        Node<K, V> *child = parent->pRight;
        grand->pLeft = child;
        parent->pRight = grand;
        after_rotate(grand, parent, child);
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child) {
        parent->pParent = grand->pParent;
        if (grand->ispLeft())
            grand->pParent->pLeft = parent;
        else if (grand->ispRight())
            grand->pParent->pRight = parent;
        else
            _table[get_index(grand)] = parent;
        if (child != nullptr)
            child->pParent = grand;
        grand->pParent = parent;
    }

    template<typename K, typename V>
    inline HashMap<K, V>::Node<K, V> *HashMap<K, V>::setmColor(Node<K, V> *node, bool color) {
        if (node != nullptr)
            node->mColor = color;
        return node;
    }

    template<typename K, typename V>
    inline void HashMap<K, V>::clear_recu(Node<K, V> *root) {
        if (root != nullptr) {
            clear_recu(root->pLeft);
            clear_recu(root->pRight);
            delete root;
        }
    }
} // namespace app

#endif /* HASH_MAP_HPP */