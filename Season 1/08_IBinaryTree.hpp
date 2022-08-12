#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <memory>
#include <queue>
#include <cmath>
#include <stack>
#include "./IString.hpp"

using namespace std;

namespace app {
    /**
     * @brief 二叉树基类
     * @date 2022-04-10
     * @tparam T
     */
    template<typename T>
    class IBinaryTree {
        friend ostream &operator<<(ostream &os, const IBinaryTree<T> &tree) { return drawmTree(os, tree); }

    protected:
        using TraverseFunc = bool (*)(shared_ptr <T> data);
        using Comparator = int (*)(shared_ptr <T> a, shared_ptr <T> b);

        template<typename U>
        struct Node : public IString {
            friend ostream &operator<<(ostream &os, const Node<U> &node) { return os << node.to_string(); }

            shared_ptr <U> pData = nullptr;
            Node<U> *pParent = nullptr, *pLeft = nullptr, *pRight = nullptr;

            Node<U> &operator=(const Node<U> &node);

            Node<U> &operator=(Node<U> &&node) noexcept;

            Node(shared_ptr <U> data, Node<U> *parent = nullptr, Node<U> *left = nullptr, Node<U> *right = nullptr)
                    : pData(data), pParent(parent), pLeft(left), pRight(right) {}

            Node(const Node<U> &node) { *this = node; }

            Node(Node<U> &&node) noexcept { *this = move(node); }

            virtual ~Node() { pData = nullptr; }

            bool is_leaf() const { return pLeft == nullptr && pRight == nullptr; }

            bool is_binary() const { return pLeft != nullptr && pRight != nullptr; }

            bool ispLeft() const { return pParent != nullptr && this == pParent->pLeft; }

            bool ispRight() const { return pParent != nullptr && this == pParent->pRight; }

            Node<U> *get_sibling() const;

            string to_string() const override { return ((IString &) *pData).to_string(); }
        };

        size_t mSize = 0;
        Comparator mComparator = nullptr;
        Node<T> *pRoot = nullptr;

        void not_null_check(shared_ptr <T> data) const {
            if (data == nullptr)
                throw invalid_argument("data must be not null.");
        }

        static ostream &drawmTree(ostream &os, const IBinaryTree<T> &tree);

        virtual Node<T> *get_node(shared_ptr <T> data) const = 0;

        virtual Node<T> *create_node(shared_ptr <T> data, Node<T> *parent) { return new Node<T>(data, parent); }

        Node<T> *get_predecessor(Node<T> *node) const;

        Node<T> *get_successor(Node<T> *node) const;

        void inorder_recu(Node<T> *node, TraverseFunc func) const;

        void preorder_recu(Node<T> *node, TraverseFunc func) const;

        void postorder_recu(Node<T> *node, TraverseFunc func) const;

        void inorder_iter(TraverseFunc func) const;

        void preorder_iter(TraverseFunc func) const;

        void postorder_iter(TraverseFunc func) const;

        void inorder_morris(TraverseFunc func) const;

        void levelorder(Node<T> *node, TraverseFunc func) const;

        size_t height_recu(Node<T> *node) const {
            if (node != nullptr)
                return 1 + max(height_recu(node->pLeft), height_recu(node->pRight));
            return 0;
        }

        size_t height_iter(Node<T> *node) const;

        void clear_recu(Node<T> *node);

    public:
        enum class TraverseOrder {
            In,
            Pre,
            Post,
            Level
        };

        IBinaryTree(Comparator comparator = nullptr) { mComparator = comparator; }

        virtual ~IBinaryTree() { clear_recu(pRoot); }

        virtual void add(shared_ptr <T> data) = 0;

        virtual void remove(shared_ptr <T> data) = 0;

        size_t size() const { return mSize; }

        size_t height() const { return height_iter(pRoot); }

        bool is_empty() const { return mSize == 0; }

        bool is_complete() const;

        bool contains(shared_ptr <T> data) const { return get_node(data) != nullptr; }

        void traverse(TraverseOrder order = TraverseOrder::In, TraverseFunc func = nullptr) const;

        void clear() {
            clear_recu(pRoot);
            pRoot = nullptr;
            mSize = 0;
        }
    };

    template<typename T>
    template<typename U>
    inline IBinaryTree<T>::Node<U> &IBinaryTree<T>::Node<U>::operator=(const IBinaryTree<T>::Node<U> &node) {
        pData = node.pData;
        pParent = node.pParent;
        pLeft = node.pLeft;
        pRight = node.pRight;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline IBinaryTree<T>::Node<U> &IBinaryTree<T>::Node<U>::operator=(Node<U> &&node) noexcept {
        pData = nullptr;
        this = &node;
        return *this;
    }

    template<typename T>
    template<typename U>
    inline IBinaryTree<T>::Node<U> *IBinaryTree<T>::Node<U>::get_sibling() const {
        if (ispLeft())
            return pParent->pRight;
        else if (ispRight())
            return pParent->pLeft;
        return nullptr;
    }

    template<typename T>
    inline ostream &IBinaryTree<T>::drawmTree(ostream &os, const IBinaryTree<T> &tree) {
        if (tree.pRoot != nullptr) {
            size_t height = 0;
            size_t level_count = 1;
            queue<Node < T> *> q;
            q.push(tree.pRoot);
            while (!q.empty()) {
                Node <T> *elem = q.front();
                if (elem != nullptr)
                    os << *tree.get_node(elem->pData) << "\t";
                q.pop();
                if (elem != nullptr)
                    q.push(elem->pLeft);
                if (elem != nullptr)
                    q.push(elem->pRight);
                level_count--;
                if (level_count == 0) {
                    level_count = q.size();
                    height++;
                    os << "\n";
                }
            }
        }
        return os;
    }

    template<typename T>
    inline IBinaryTree<T>::Node<T> *IBinaryTree<T>::get_predecessor(Node<T> *node) const {
        if (node != nullptr) {
            Node <T> *p = node->pLeft;
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

    template<typename T>
    inline IBinaryTree<T>::Node<T> *IBinaryTree<T>::get_successor(Node<T> *node) const {
        if (node != nullptr) {
            Node <T> *p = node->pRight;
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

    template<typename T>
    inline bool IBinaryTree<T>::is_complete() const {
        if (pRoot != nullptr) {
            queue<Node < T> *> q;
            q.push(pRoot);
            bool leaf = false;
            while (!q.empty()) {
                Node <T> *elem = q.front();
                q.pop();
                if (leaf && !elem->is_leaf())
                    return false;

                if (elem->pLeft != nullptr)
                    q.push(elem->pLeft);
                else if (elem->pRight != nullptr)
                    return false;

                if (elem->pRight != nullptr)
                    q.push(elem->pRight);
                else
                    leaf = true; //最后一个非叶结点不入队
            }
            return true;
        }
        return false;
    }

    template<typename T>
    inline void IBinaryTree<T>::clear_recu(Node<T> *node) {
        if (node != nullptr) {
            clear_recu(node->pLeft);
            clear_recu(node->pRight);
            delete node;
        }
    }

    template<typename T>
    inline size_t IBinaryTree<T>::height_iter(Node<T> *node) const {
        if (node != nullptr) {
            size_t height = 0, level_count = 1;
            queue<Node < T> *> q;
            q.push(node);
            while (!q.empty()) {
                Node <T> *elem = q.front();
                q.pop();
                level_count--;
                if (elem->pLeft != nullptr)
                    q.push(elem->pLeft);
                if (elem->pRight != nullptr)
                    q.push(elem->pRight);
                if (level_count == 0) {
                    level_count = q.size();
                    height++;
                }
            }
            return height;
        }
        return 0;
    }

    template<typename T>
    inline void IBinaryTree<T>::traverse(TraverseOrder order, TraverseFunc func) const {
        switch (order) {
            case TraverseOrder::In:
                inorder_recu(pRoot, func);
                break;
            case TraverseOrder::Pre:
                preorder_recu(pRoot, func);
                break;
            case TraverseOrder::Post:
                postorder_recu(pRoot, func);
                break;
            case TraverseOrder::Level:
                levelorder(pRoot, func);
                break;
        }
    }

    template<typename T>
    inline void IBinaryTree<T>::inorder_recu(Node<T> *node, TraverseFunc func) const {
        if (node != nullptr) {
            inorder_recu(node->pLeft, func);
            if (func != nullptr)
                func(node->pData);
            else
                cout << *node->pData << "\n";
            inorder_recu(node->pRight, func);
        }
    }

    template<typename T>
    inline void IBinaryTree<T>::preorder_recu(Node<T> *node, TraverseFunc func) const {
        if (node != nullptr) {
            if (func != nullptr)
                func(node->pData);
            else
                cout << *node->pData << "\n";
            preorder_recu(node->pLeft, func);
            preorder_recu(node->pRight, func);
        }
    }

    template<typename T>
    inline void IBinaryTree<T>::postorder_recu(Node<T> *node, TraverseFunc func) const {
        if (node != nullptr) {
            postorder_recu(node->pLeft, func);
            postorder_recu(node->pRight, func);
            if (func != nullptr)
                func(node->pData);
            else
                cout << *node->pData << "\n";
        }
    }

    template<typename T>
    inline void IBinaryTree<T>::inorder_iter(TraverseFunc func) const {
        if (pRoot != nullptr) {
            Node <T> *node = pRoot;
            stack<Node < T> *> s;
            while (true) {
                if (node != nullptr) {
                    s.push(node);
                    node = node->pLeft;
                } else if (!s.empty()) {
                    node = s.top();
                    s.pop();
                    if (func != nullptr)
                        func(node->pData);
                    else
                        cout << *node->pData << "\n";
                    node = node->pRight;
                } else
                    return;
            }
        }
    }

    template<typename T>
    inline void IBinaryTree<T>::preorder_iter(TraverseFunc func) const {
        if (pRoot != nullptr) {
            stack<Node < T> *> s;
            s.push(pRoot);
            while (!s.empty()) {
                Node <T> *node = s.top();
                s.pop();
                if (func != nullptr)
                    func(node->pData);
                else
                    cout << *node->pData << "\n";
                if (node->pRight != nullptr)
                    s.push(node->pRight);
                if (node->pLeft != nullptr)
                    s.push(node->pLeft);
            }
        }
    }

    template<typename T>
    inline void IBinaryTree<T>::postorder_iter(TraverseFunc func) const {
        if (pRoot != nullptr) {
            Node <T> *prev = nullptr;
            stack<Node < T> *> s;
            s.push(pRoot);
            while (!s.empty()) {
                Node <T> *top = s.top();
                if (top->is_leaf() || (prev != nullptr && prev->pParent == top)) {
                    prev = s.pop();
                    if (func != nullptr)
                        func(prev->pData);
                    else
                        cout << *prev->pData << "\n";
                } else {
                    if (top->pRight != nullptr)
                        s.push(top->pRight);
                    if (top->pLeft != nullptr)
                        s.push(top->pLeft);
                }
            }
        }
    }

    template<typename T>
    inline void IBinaryTree<T>::inorder_morris(TraverseFunc func) const {
        Node <T> *node = pRoot;
        while (node != nullptr) {
            if (node->pLeft != nullptr) {
                Node <T> *pred = node->pLeft;
                while (pred->pRight != nullptr && pred->pRight != node)
                    pred = pred->pRight;
                if (pred->pRight == nullptr) {
                    pred->pRight = node;
                    node = node->pLeft;
                } else {
                    if (func != nullptr)
                        func(node->pData);
                    else
                        cout << *node->pData << "\n";
                    pred->pRight = nullptr;
                    node = node->pRight;
                }
            } else {
                if (func != nullptr)
                    func(node->pData);
                else
                    cout << *node->pData << "\n";
                node = node->pRight;
            }
        }
    }

    template<typename T>
    inline void IBinaryTree<T>::levelorder(Node<T> *node, TraverseFunc func) const {
        if (node != nullptr) {
            queue<Node < T> *> q;
            q.push(node);
            while (!q.empty()) {
                Node <T> *elem = q.front();
                q.pop();
                if (elem->pLeft != nullptr)
                    q.push(elem->pLeft);
                if (elem->pRight != nullptr)
                    q.push(elem->pRight);
                if (func != nullptr)
                    func(elem->pData);
                else
                    cout << *elem->pData << "\n";
            }
        }
    }
} // namespace app

#endif /* BINARY_TREE_HPP */