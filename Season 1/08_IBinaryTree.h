#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <iostream>
#include <memory>
#include <queue>
#include <cmath>
#include <stack>
#include "./IString.h"
/**
 * @brief 二叉树基类
 * @date 2022-04-10
 * @tparam T
 */
template <typename T>
class IBinaryTree
{
    friend std::ostream &operator<<(std::ostream &os, const IBinaryTree<T> &tree) { return draw_tree(os, tree); }

protected:
    using TraverseFunc = bool (*)(std::shared_ptr<T> data);
    using Comparator = int (*)(std::shared_ptr<T> a, std::shared_ptr<T> b);
    template <typename U>
    struct Node : public IString
    {
        friend std::ostream &operator<<(std::ostream &os, const Node<U> &node) { return os << node.to_string(); }
        std::shared_ptr<U> _data = nullptr;
        Node<U> *_parent = nullptr, *_left = nullptr, *_right = nullptr;
        Node<U> &operator=(const Node<U> &node);
        Node<U> &operator=(Node<U> &&node) noexcept;
        Node(std::shared_ptr<U> data, Node<U> *parent = nullptr, Node<U> *left = nullptr, Node<U> *right = nullptr)
            : _data(data), _parent(parent), _left(left), _right(right) {}
        Node(const Node<U> &node) { *this = node; }
        Node(Node<U> &&node) noexcept { *this = std::move(node); }
        virtual ~Node() { _data = nullptr; }
        bool is_leaf() const { return _left == nullptr && _right == nullptr; }
        bool is_binary() const { return _left != nullptr && _right != nullptr; }
        bool is_left() const { return _parent != nullptr && this == _parent->_left; }
        bool is_right() const { return _parent != nullptr && this == _parent->_right; }
        Node<U> *get_sibling() const;
        std::string to_string() const override { return ((IString &)*_data).to_string(); }
    };
    size_t _size = 0;
    Node<T> *_root = nullptr;
    Comparator _comparator = nullptr;
    void not_null_check(std::shared_ptr<T> data) const
    {
        if (data == nullptr)
            throw std::invalid_argument("data must be not null.");
    }
    static std::ostream &draw_tree(std::ostream &os, const IBinaryTree<T> &tree);
    virtual Node<T> *get_node(std::shared_ptr<T> data) const = 0;
    virtual Node<T> *create_node(std::shared_ptr<T> data, Node<T> *parent) { return new Node<T>(data, parent); }
    Node<T> *get_predecessor(Node<T> *node) const;
    Node<T> *get_successor(Node<T> *node) const;
    void inorder_recu(Node<T> *node, TraverseFunc func) const;
    void preorder_recu(Node<T> *node, TraverseFunc func) const;
    void postorder_recu(Node<T> *node, TraverseFunc func) const;
    void inorder_iter(TraverseFunc func) const;
    void preorder_iter(TraverseFunc func) const;
    void postorder_iter(TraverseFunc func) const;
    void levelorder(Node<T> *node, TraverseFunc func) const;
    size_t height_recu(Node<T> *node) const
    {
        if (node != nullptr)
            return 1 + std::max(height_recu(node->_left), height_recu(node->_right));
        return 0;
    }
    size_t height_iter(Node<T> *node) const;
    void clear_recu(Node<T> *node);

public:
    enum class TraverseOrder
    {
        In,
        Pre,
        Post,
        Level
    };
    IBinaryTree(Comparator comparator = nullptr) { _comparator = comparator; }
    virtual ~IBinaryTree() { clear_recu(_root); }
    virtual void add(std::shared_ptr<T> data) = 0;
    virtual void remove(std::shared_ptr<T> data) = 0;
    size_t size() const { return _size; }
    size_t height() const { return height_iter(_root); }
    bool is_empty() const { return _size == 0; }
    bool is_complete() const;
    bool contains(std::shared_ptr<T> data) const { return get_node(data) != nullptr; }
    void traverse(TraverseOrder order = TraverseOrder::In, TraverseFunc func = nullptr) const;
    void clear()
    {
        clear_recu(_root);
        _root = nullptr;
        _size = 0;
    }
};

template <typename T>
template <typename U>
inline IBinaryTree<T>::Node<U> &IBinaryTree<T>::Node<U>::operator=(const IBinaryTree<T>::Node<U> &node)
{
    _data = node._data;
    _parent = node._parent;
    _left = node._left;
    _right = node._right;
    return *this;
}

template <typename T>
template <typename U>
inline IBinaryTree<T>::Node<U> &IBinaryTree<T>::Node<U>::operator=(Node<U> &&node) noexcept
{
    _data = nullptr;
    this = &node;
    return *this;
}

template <typename T>
template <typename U>
inline IBinaryTree<T>::Node<U> *IBinaryTree<T>::Node<U>::get_sibling() const
{
    if (is_left())
        return _parent->_right;
    else if (is_right())
        return _parent->_left;
    return nullptr;
}

template <typename T>
inline std::ostream &IBinaryTree<T>::draw_tree(std::ostream &os, const IBinaryTree<T> &tree)
{
    if (tree._root != nullptr)
    {
        size_t height = 0;
        size_t level_count = 1;
        std::queue<Node<T> *> q;
        q.push(tree._root);
        while (!q.empty())
        {
            Node<T> *elem = q.front();
            if (elem != nullptr)
                os << *tree.get_node(elem->_data) << "\t";
            q.pop();
            if (elem != nullptr)
                q.push(elem->_left);
            if (elem != nullptr)
                q.push(elem->_right);
            level_count--;
            if (level_count == 0)
            {
                level_count = q.size();
                height++;
                os << "\n";
            }
        }
    }
    return os;
}

template <typename T>
inline IBinaryTree<T>::Node<T> *IBinaryTree<T>::get_predecessor(Node<T> *node) const
{
    if (node != nullptr)
    {
        Node<T> *p = node->_left;
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

template <typename T>
inline IBinaryTree<T>::Node<T> *IBinaryTree<T>::get_successor(Node<T> *node) const
{
    if (node != nullptr)
    {
        Node<T> *p = node->_right;
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

template <typename T>
inline bool IBinaryTree<T>::is_complete() const
{
    if (_root != nullptr)
    {
        std::queue<Node<T> *> q;
        q.push(_root);
        bool leaf = false;
        while (!q.empty())
        {
            Node<T> *elem = q.front();
            q.pop();
            if (leaf && !elem->is_leaf())
                return false;

            if (elem->_left != nullptr)
                q.push(elem->_left);
            else if (elem->_right != nullptr)
                return false;

            if (elem->_right != nullptr)
                q.push(elem->_right);
            else
                leaf = true; //最后一个非叶结点不入队
        }
        return true;
    }
    return false;
}

template <typename T>
inline void IBinaryTree<T>::clear_recu(Node<T> *node)
{
    if (node != nullptr)
    {
        clear_recu(node->_left);
        clear_recu(node->_right);
        delete node;
    }
}

template <typename T>
inline size_t IBinaryTree<T>::height_iter(Node<T> *node) const
{
    if (node != nullptr)
    {
        size_t height = 0, level_count = 1;
        std::queue<Node<T> *> q;
        q.push(node);
        while (!q.empty())
        {
            Node<T> *elem = q.front();
            q.pop();
            level_count--;
            if (elem->_left != nullptr)
                q.push(elem->_left);
            if (elem->_right != nullptr)
                q.push(elem->_right);
            if (level_count == 0)
            {
                level_count = q.size();
                height++;
            }
        }
        return height;
    }
    return 0;
}

template <typename T>
inline void IBinaryTree<T>::traverse(TraverseOrder order, TraverseFunc func) const
{
    switch (order)
    {
    case TraverseOrder::In:
        inorder_recu(_root, func);
        break;
    case TraverseOrder::Pre:
        preorder_recu(_root, func);
        break;
    case TraverseOrder::Post:
        postorder_recu(_root, func);
        break;
    case TraverseOrder::Level:
        levelorder(_root, func);
        break;
    }
}

template <typename T>
inline void IBinaryTree<T>::inorder_recu(Node<T> *node, TraverseFunc func) const
{
    if (node != nullptr)
    {
        inorder_recu(node->_left, func);
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data << "\n";
        inorder_recu(node->_right, func);
    }
}

template <typename T>
inline void IBinaryTree<T>::preorder_recu(Node<T> *node, TraverseFunc func) const
{
    if (node != nullptr)
    {
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data << "\n";
        preorder_recu(node->_left, func);
        preorder_recu(node->_right, func);
    }
}

template <typename T>
inline void IBinaryTree<T>::postorder_recu(Node<T> *node, TraverseFunc func) const
{
    if (node != nullptr)
    {
        postorder_recu(node->_left, func);
        postorder_recu(node->_right, func);
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data << "\n";
    }
}

template <typename T>
inline void IBinaryTree<T>::inorder_iter(TraverseFunc func) const
{
    if (_root != nullptr)
    {
        Node<T> *node = _root;
        std::stack<Node<T> *> s;
        while (true)
        {
            if (node != nullptr)
            {
                s.push(node);
                node = node->_left;
            }
            else if (!s.empty())
            {
                node = s.top();
                s.pop();
                if (func != nullptr)
                    func(node->_data);
                else
                    std::cout << *node->_data << "\n";
                node = node->_right;
            }
            else
                return;
        }
    }
}

template <typename T>
inline void IBinaryTree<T>::preorder_iter(TraverseFunc func) const
{
    if (_root != nullptr)
    {
        std::stack<Node<T> *> s;
        s.push(_root);
        while (!s.empty())
        {
            Node<T> *node = s.top();
            s.pop();
            if (func != nullptr)
                func(node->_data);
            else
                std::cout << *node->_data << "\n";
            if (node->_right != nullptr)
                s.push(node->_right);
            if (node->_left != nullptr)
                s.push(node->_left);
        }
    }
}

template <typename T>
inline void IBinaryTree<T>::postorder_iter(TraverseFunc func) const
{
    if(_root != nullptr)
    {
        Node<T> *prev = nullptr;
        std::stack<Node<T> *> s;
        s.push(_root);
        while (!s.empty())
        {
            Node<T> *top = s.top();
            if(top->is_leaf() || (prev != nullptr && prev->_parent == top))
            {
                prev = s.pop();
                if (func != nullptr)
                    func(prev->_data);
                else
                    std::cout << *prev->_data << "\n";
            }
            else
            {
                if(top->_right != nullptr)
                    s.push(top->_right);
                if(top->_left != nullptr)
                    s.push(top->_left);
            }
        }
    }
}

template <typename T>
inline void IBinaryTree<T>::levelorder(Node<T> *node, TraverseFunc func) const
{
    if (node != nullptr)
    {
        std::queue<Node<T> *> q;
        q.push(node);
        while (!q.empty())
        {
            Node<T> *elem = q.front();
            q.pop();
            if (elem->_left != nullptr)
                q.push(elem->_left);
            if (elem->_right != nullptr)
                q.push(elem->_right);
            if (func != nullptr)
                func(elem->_data);
            else
                std::cout << *elem->_data << "\n";
        }
    }
}

#endif /* BINARY_TREE_H */