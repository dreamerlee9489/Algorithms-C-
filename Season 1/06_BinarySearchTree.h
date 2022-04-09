#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>

template <typename T>
class BinarySearchTree
{
    // typedef void traverse_func(std::shared_ptr<T> data);
    using traverse_func = void (*)(std::shared_ptr<T> data);

private:
    template <typename U>
    struct Node
    {
        std::shared_ptr<U> _data;
        Node<U> *_parent, *_left, *_right;
        Node(std::shared_ptr<U> data, Node<U> *parent = nullptr, Node<U> *left = nullptr, Node<U> *right = nullptr)
            : _data(data), _parent(parent), _left(left), _right(right) {}
        ~Node() { _data = nullptr; }
        bool is_leaf() { return _left == nullptr && _right == nullptr; }
        bool is_binary() { return _left != nullptr && _right != nullptr; }
    };
    size_t _size = 0;
    void nullptr_check(std::shared_ptr<T> data) const;
    Node<T> *get_predecessor(Node<T> *node) const;
    Node<T> *get_successor(Node<T> *node) const;
    void inorder_traverse(Node<T> *node, traverse_func func) const;
    void preorder_traverse(Node<T> *node, traverse_func func) const;
    void postorder_traverse(Node<T> *node, traverse_func func) const;
    void levelorder_traverse(Node<T> *node, traverse_func func) const;
    size_t height_recu(Node<T> *node) const;
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
    Node<T> *_root = nullptr;
    BinarySearchTree() = default;
    ~BinarySearchTree() { clear_recu(_root); }
    size_t size() const { return _size; }
    size_t height() const { return height_iter(_root); }
    bool is_empty() const { return _size == 0; }
    bool is_complete();
    Node<T> *get_node(std::shared_ptr<T> data) const;
    void add(std::shared_ptr<T> data);
    void remove(std::shared_ptr<T> data);
    bool contains(std::shared_ptr<T> data) const;
    void traverse(TraverseOrder order = TraverseOrder::In, traverse_func func = nullptr) const;
    void clear() { clear_recu(_root); }
};

template <typename T>
size_t BinarySearchTree<T>::height_recu(Node<T> *node) const
{
    if (node == nullptr)
        return 0;
    return 1 + std::max(height_recu(node->_left), height_recu(node->_right));
}

template <typename T>
size_t BinarySearchTree<T>::height_iter(Node<T> *node) const
{
    if (node == nullptr)
        return 0;
    std::queue<Node<T> *> q = std::queue<Node<T> *>();
    q.push(node);
    size_t height = 0, level_count = 1;
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

template <typename T>
bool BinarySearchTree<T>::is_complete()
{
    if (_root == nullptr)
        return false;
    std::queue<Node<T> *> q = std::queue<Node<T> *>();
    q.push(_root);
    bool leaf = false;
    while (!q.empty())
    {
        Node<T> *elem = q.front();
        q.pop();
        if (leaf && !elem->is_leaf())
            return false;
        if (elem->is_binary())
        {
            q.push(elem->_left);
            q.push(elem->_right);
        }
        else if (elem->_left == nullptr && elem->_right != nullptr)
            return false;
        else
            leaf = true;
    }
    return true;
}

template <typename T>
BinarySearchTree<T>::Node<T> *BinarySearchTree<T>::get_predecessor(Node<T> *node) const
{
    if (node == nullptr)
        return nullptr;
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

template <typename T>
BinarySearchTree<T>::Node<T> *BinarySearchTree<T>::get_successor(Node<T> *node) const
{
    if (node == nullptr)
        return nullptr;
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

template <typename T>
void BinarySearchTree<T>::add(std::shared_ptr<T> data)
{
    nullptr_check(data);
    if (_root == nullptr)
    {
        _root = new Node<T>(data);
        _size++;
        return;
    }
    Node<T> *node = _root, *parent = _root;
    while (node != nullptr)
    {
        parent = node;
        if (*node->_data < *data)
            node = node->_right;
        else if (*node->_data > *data)
            node = node->_left;
        else
        {
            node->_data = data;
            return;
        }
    }
    Node<T> *temp = new Node<T>(data, parent);
    if (*data > *parent->_data)
        parent->_right = temp;
    else
        parent->_left = temp;
    _size++;
}

template <typename T>
void BinarySearchTree<T>::remove(std::shared_ptr<T> data)
{
}

template <typename T>
bool BinarySearchTree<T>::contains(std::shared_ptr<T> data) const
{
    return get_node(data) != nullptr;
}

template <typename T>
void BinarySearchTree<T>::traverse(TraverseOrder order, traverse_func func) const
{
    switch (order)
    {
    case TraverseOrder::In:
        inorder_traverse(_root, func);
        break;
    case TraverseOrder::Pre:
        preorder_traverse(_root, func);
        break;
    case TraverseOrder::Post:
        postorder_traverse(_root, func);
        break;
    case TraverseOrder::Level:
        levelorder_traverse(_root, func);
        break;
    }
}

template <typename T>
void BinarySearchTree<T>::clear_recu(Node<T> *node)
{
    if (node != nullptr)
    {
        if (node->_left != nullptr)
            clear_recu(node->_left);
        if (node->_right != nullptr)
            clear_recu(node->_right);
        delete node;
        _root = nullptr;
    }
}

template <typename T>
void BinarySearchTree<T>::nullptr_check(std::shared_ptr<T> data) const
{
    if (data == nullptr)
        throw std::invalid_argument("data must be not null.");
}

template <typename T>
BinarySearchTree<T>::Node<T> *BinarySearchTree<T>::get_node(std::shared_ptr<T> data) const
{
    Node<T> *node = _root;
    while (node != nullptr)
    {
        if (*node->_data < *data)
            node = node->_right;
        else if (*node->_data > *data)
            node = node->_left;
        else
            return node;
    }
    return nullptr;
}

template <typename T>
void BinarySearchTree<T>::inorder_traverse(Node<T> *node, traverse_func func) const
{
    if (node != nullptr)
    {
        inorder_traverse(node->_left, func);
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data << "\n";
        inorder_traverse(node->_right, func);
    }
}

template <typename T>
void BinarySearchTree<T>::preorder_traverse(Node<T> *node, traverse_func func) const
{
    if (node != nullptr)
    {
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data << "\n";
        preorder_traverse(node->_left, func);
        preorder_traverse(node->_right, func);
    }
}

template <typename T>
void BinarySearchTree<T>::postorder_traverse(Node<T> *node, traverse_func func) const
{
    if (node != nullptr)
    {
        postorder_traverse(node->_left, func);
        postorder_traverse(node->_right, func);
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data << "\n";
    }
}

template <typename T>
void BinarySearchTree<T>::levelorder_traverse(Node<T> *node, traverse_func func) const
{
    if (node == nullptr)
        return;
    std::queue<Node<T> *> q = std::queue<Node<T> *>();
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

#endif /* BINARY_SEARCH_TREE_H */
