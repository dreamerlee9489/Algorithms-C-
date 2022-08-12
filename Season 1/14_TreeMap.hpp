#ifndef TREE_MAP_HPP
#define TREE_MAP_HPP

#include "./14_IMap.hpp"

namespace app {
    /**
     * @brief 红黑树映射
     * @date 2022-04-17
     * @tparam K
     * @tparam V
     */
    template<typename K, typename V>
    class TreeMap : public IMap<K, V> {
        static const bool BLACK = false, RED = true;

        template<typename _K, typename _V>
        struct Node {
            friend ostream &operator<<(ostream &os, const Node &node) {
                return os << "<" << *node.pKey << "-" << *node.mValue << ">";
            }

            bool mColor = RED;
            shared_ptr<_K> pKey;
            shared_ptr<_V> mValue;
            Node<_K, _V> *pParent = nullptr, *pLeft = nullptr, *pRight = nullptr;

            Node<_K, _V> &operator=(const Node<_K, _V> &node);

            Node<_K, _V> &operator=(Node<_K, _V> &&node) noexcept;

            Node(shared_ptr<_K> key, shared_ptr<_V> value, Node<_K, _V> *parent = nullptr, Node<_K, _V> *left = nullptr,
                 Node<_K, _V> *right = nullptr)
                    : pKey(key), mValue(value), pParent(parent), pLeft(left), pRight(right) {}

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

        size_t mSize = 0;
        Node<K, V> *pRoot = nullptr;
        typename IMap<K, V>::Comparator mComparator = nullptr;

        void not_null_check(shared_ptr<K> key) const {
            if (key == nullptr)
                throw invalid_argument("key must be not null.");
        }

        Node<K, V> *get_node(shared_ptr<K> key) const;

        Node<K, V> *get_predecessor(Node<K, V> *node) const;

        Node<K, V> *get_successor(Node<K, V> *node) const;

        void after_add(Node<K, V> *node);

        void after_remove(Node<K, V> *node);

        void rotatepLeft(Node<K, V> *grand);

        void rotatepRight(Node<K, V> *grand);

        void after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child);

        Node<K, V> *setmColor(Node<K, V> *node, bool color);

        bool color_of(Node<K, V> *node) const { return node == nullptr ? BLACK : node->mColor; }

        bool is_black(Node<K, V> *node) const { return color_of(node) == BLACK; }

        bool is_red(Node<K, V> *node) const { return color_of(node) == RED; }

        void inorder_traverse(Node<K, V> *node, typename IMap<K, V>::TraverseFunc func = nullptr) const;

        void clear_recu(Node<K, V> *node);

    public:
        TreeMap<K, V> &operator=(const TreeMap<K, V> &map);

        TreeMap<K, V> &operator=(TreeMap<K, V> &&map) noexcept;

        TreeMap(typename IMap<K, V>::Comparator comparator = nullptr) { mComparator = comparator; }

        TreeMap(const TreeMap<K, V> &map) { *this = map; }

        TreeMap(TreeMap<K, V> &&map) noexcept { *this = move(map); }

        ~TreeMap() { clear_recu(pRoot); }

        size_t size() const override { return mSize; }

        bool is_empty() const override { return mSize == 0; }

        bool containspKey(shared_ptr<K> key) const override { return get_node(key) != nullptr; }

        bool containsmValue(shared_ptr<V> value) const override;

        shared_ptr<V> getmValue(shared_ptr<K> key) const override {
            Node<K, V> *node = get_node(key);
            return node != nullptr ? node->mValue : nullptr;
        }

        shared_ptr<V> add(shared_ptr<K> key, shared_ptr<V> value) override;

        shared_ptr<V> remove(shared_ptr<K> key) override;

        void traverse(typename IMap<K, V>::TraverseFunc func = nullptr) const { inorder_traverse(pRoot, func); }

        void clear() override {
            clear_recu(pRoot);
            pRoot = nullptr;
            mSize = 0;
        }
    };

    template<typename K, typename V>
    template<typename _K, typename _V>
    inline TreeMap<K, V>::Node<_K, _V> &TreeMap<K, V>::Node<_K, _V>::operator=(const Node<_K, _V> &node) {
        pKey = node.pKey;
        mValue = node.mValue;
        pParent = node.pParent;
        pLeft = node.pLeft;
        pRight = node.pRight;
        mColor = node.mColor;
        return *this;
    }

    template<typename K, typename V>
    template<typename _K, typename _V>
    inline TreeMap<K, V>::Node<_K, _V> &TreeMap<K, V>::Node<_K, _V>::operator=(Node<_K, _V> &&node) noexcept {
        pKey = nullptr;
        mValue = nullptr;
        this = &node;
        return *this;
    }

    template<typename K, typename V>
    template<typename _K, typename _V>
    inline TreeMap<K, V>::Node<_K, _V> *TreeMap<K, V>::Node<_K, _V>::get_sibling() const {
        if (ispLeft())
            return pParent->pRight;
        else if (ispRight())
            return pParent->pLeft;
        return nullptr;
    }

    template<typename K, typename V>
    inline TreeMap<K, V> &TreeMap<K, V>::operator=(const TreeMap<K, V> &map) {
        clear();
        if (map.mSize > 0) {
            mComparator = map.mComparator;
            queue<Node<K, V> *> q;
            q.push(map.pRoot);
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
        return *this;
    }

    template<typename K, typename V>
    inline TreeMap<K, V> &TreeMap<K, V>::operator=(TreeMap<K, V> &&map) noexcept {
        clear();
        mSize = map.mSize;
        pRoot = map.pRoot;
        mComparator = map.mComparator;
        map.mSize = 0;
        map.pRoot = nullptr;
        map.mComparator = nullptr;
        return *this;
    }

    template<typename K, typename V>
    inline TreeMap<K, V>::Node<K, V> *TreeMap<K, V>::get_node(shared_ptr<K> key) const {
        Node<K, V> *node = pRoot;
        while (node != nullptr) {
            if (mComparator == nullptr) {
                if (*node->pKey < *key)
                    node = node->pRight;
                else if (*node->pKey > *key)
                    node = node->pLeft;
                else
                    return node;
            } else {
                if (mComparator(node->pKey, key) < 0)
                    node = node->pRight;
                else if (mComparator(node->pKey, key) > 0)
                    node = node->pLeft;
                else
                    return node;
            }
        }
        return nullptr;
    }

    template<typename K, typename V>
    inline TreeMap<K, V>::Node<K, V> *TreeMap<K, V>::get_predecessor(Node<K, V> *node) const {
        if (node != nullptr) {
            Node<K, V> *p = node->pLeft;
            if (p != nullptr) {
                while (p->pRight != nullptr)
                    p = p->pRight;
                return p;
            }
            while (node->pParent != nullptr && node == node->pParent->pLeft)
                node = node->pParent;
            return node->pParent;
        }
        return nullptr;
    }

    template<typename K, typename V>
    inline TreeMap<K, V>::Node<K, V> *TreeMap<K, V>::get_successor(Node<K, V> *node) const {
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
    inline void TreeMap<K, V>::after_add(Node<K, V> *node) {
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
    inline void TreeMap<K, V>::after_remove(Node<K, V> *node) {
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
    inline void TreeMap<K, V>::rotatepLeft(Node<K, V> *grand) {
        Node<K, V> *parent = grand->pRight;
        Node<K, V> *child = parent->pLeft;
        grand->pRight = child;
        parent->pLeft = grand;
        after_rotate(grand, parent, child);
    }

    template<typename K, typename V>
    inline void TreeMap<K, V>::rotatepRight(Node<K, V> *grand) {
        Node<K, V> *parent = grand->pLeft;
        Node<K, V> *child = parent->pRight;
        grand->pLeft = child;
        parent->pRight = grand;
        after_rotate(grand, parent, child);
    }

    template<typename K, typename V>
    inline void TreeMap<K, V>::after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child) {
        parent->pParent = grand->pParent;
        if (grand->ispLeft())
            grand->pParent->pLeft = parent;
        else if (grand->ispRight())
            grand->pParent->pRight = parent;
        else
            pRoot = parent;
        if (child != nullptr)
            child->pParent = grand;
        grand->pParent = parent;
    }

    template<typename K, typename V>
    inline TreeMap<K, V>::Node<K, V> *TreeMap<K, V>::setmColor(Node<K, V> *node, bool color) {
        if (node != nullptr)
            node->mColor = color;
        return node;
    }

    template<typename K, typename V>
    inline void TreeMap<K, V>::clear_recu(Node<K, V> *node) {
        if (node != nullptr) {
            clear_recu(node->pLeft);
            clear_recu(node->pRight);
            delete node;
        }
    }

    template<typename K, typename V>
    inline bool TreeMap<K, V>::containsmValue(shared_ptr<V> value) const {
        if (pRoot != nullptr) {
            queue<Node<K, V> *> q;
            q.push(pRoot);
            while (!q.empty()) {
                Node<K, V> *node = q.front();
                if (*node->mValue == *value)
                    return true;
                q.pop();
                if (node->pLeft != nullptr)
                    q.push(node->pLeft);
                if (node->pRight != nullptr)
                    q.push(node->pRight);
            }
        }
        return false;
    }

    template<typename K, typename V>
    inline shared_ptr<V> TreeMap<K, V>::add(shared_ptr<K> key, shared_ptr<V> value) {
        not_null_check(key);
        if (pRoot == nullptr) {
            pRoot = new Node<K, V>(key, value, nullptr);
            mSize++;
            after_add(pRoot);
            return nullptr;
        }
        Node<K, V> *node = pRoot, *parent = pRoot;
        while (node != nullptr) {
            parent = node;
            if (mComparator == nullptr) {
                if (*node->pKey < *key)
                    node = node->pRight;
                else if (*node->pKey > *key)
                    node = node->pLeft;
                else {
                    node->pKey = key;
                    shared_ptr<V> old = node->mValue;
                    node->mValue = value;
                    return old;
                }
            } else {
                if (mComparator(node->pKey, key) < 0)
                    node = node->pRight;
                else if (mComparator(node->pKey, key) > 0)
                    node = node->pLeft;
                else {
                    node->pKey = key;
                    shared_ptr<V> old = node->mValue;
                    node->mValue = value;
                    return old;
                }
            }
        }
        Node<K, V> *temp = new Node<K, V>(key, value, parent);
        if (mComparator == nullptr) {
            if (*parent->pKey < *key)
                parent->pRight = temp;
            else
                parent->pLeft = temp;
        } else {
            if (mComparator(parent->pKey, key) < 0)
                parent->pRight = temp;
            else
                parent->pLeft = temp;
        }
        mSize++;
        after_add(temp);
        return nullptr;
    }

    template<typename K, typename V>
    inline shared_ptr<V> TreeMap<K, V>::remove(shared_ptr<K> key) {
        Node<K, V> *node = get_node(key);
        if (node != nullptr) {
            mSize--;
            shared_ptr<V> old = node->mValue;
            if (node->is_binary()) {
                Node<K, V> *s = get_successor(node);
                node->pKey = s->pKey;
                node->mValue = s->mValue;
                node = s; //删除前驱结点
            }
            Node<K, V> *replace = node->pLeft != nullptr ? node->pLeft : node->pRight;
            if (replace != nullptr) {
                replace->pParent = node->pParent;
                if (node->pParent == nullptr)
                    pRoot = replace;
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
                pRoot = nullptr;
            }
            delete node;
            return old;
        }
        return nullptr;
    }

    template<typename K, typename V>
    inline void TreeMap<K, V>::inorder_traverse(Node<K, V> *node, typename IMap<K, V>::TraverseFunc func) const {
        if (node != nullptr) {
            inorder_traverse(node->pLeft, func);
            if (func != nullptr)
                func(node->pKey, node->mValue);
            else
                cout << *node << "\n";
            inorder_traverse(node->pRight, func);
        }
    }
} // namespace app

#endif /* TREE_MAP_HPP */
