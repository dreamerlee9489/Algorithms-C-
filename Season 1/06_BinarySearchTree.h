#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>
#include <memory>
#include <queue>

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
    };
    size_t _size = 0;
    void nullptr_check(std::shared_ptr<T> data);
    Node<T> *get_node(std::shared_ptr<T> data);
    void inorder_traverse(Node<T> *node, traverse_func func);
    void preorder_traverse(Node<T> *node, traverse_func func);
    void postorder_traverse(Node<T> *node, traverse_func func);
    void levelorder_traverse(Node<T> *node, traverse_func func);

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
    ~BinarySearchTree() { clear(_root); }
    size_t size() { return _size; }
    bool is_empty() { return _size == 0; }
    void add(std::shared_ptr<T> data);
    void remove(std::shared_ptr<T> data);
    bool contains(std::shared_ptr<T> data);
    void traverse(TraverseOrder order = TraverseOrder::In, traverse_func func = nullptr);
    void clear(Node<T> *node);
};

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
bool BinarySearchTree<T>::contains(std::shared_ptr<T> data)
{
    return get_node(data) != nullptr;
}

template <typename T>
void BinarySearchTree<T>::traverse(TraverseOrder order, traverse_func func)
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
void BinarySearchTree<T>::clear(Node<T> *node)
{
    if (node != nullptr)
    {
        if (node->_left != nullptr)
            clear(node->_left);
        if (node->_right != nullptr)
            clear(node->_right);
        delete node;
    }
}

template <typename T>
void BinarySearchTree<T>::nullptr_check(std::shared_ptr<T> data)
{
    if (data == nullptr)
        throw std::invalid_argument("data must be not null.");
}

template <typename T>
BinarySearchTree<T>::Node<T> *BinarySearchTree<T>::get_node(std::shared_ptr<T> data)
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
void BinarySearchTree<T>::inorder_traverse(Node<T> *node, traverse_func func)
{
    if (node != nullptr)
    {
        if (node->_left != nullptr)
            inorder_traverse(node->_left, func);
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data;
        if (node->_right != nullptr)
            inorder_traverse(node->_right, func);
    }
}

template <typename T>
void BinarySearchTree<T>::preorder_traverse(Node<T> *node, traverse_func func)
{
    if (node != nullptr)
    {
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data;
        if (node->_left != nullptr)
            preorder_traverse(node->_left, func);
        if (node->_right != nullptr)
            preorder_traverse(node->_right, func);
    }
}

template <typename T>
void BinarySearchTree<T>::postorder_traverse(Node<T> *node, traverse_func func)
{
    if (node != nullptr)
    {
        if (node->_left != nullptr)
            postorder_traverse(node->_left, func);
        if (node->_right != nullptr)
            postorder_traverse(node->_right, func);
        if (func != nullptr)
            func(node->_data);
        else
            std::cout << *node->_data;
    }
}

template <typename T>
void BinarySearchTree<T>::levelorder_traverse(Node<T> *node, traverse_func func)
{
    if (node != nullptr)
    {
        std::queue<Node<T> *> q = std::queue<Node<T> *>();
        q.push(node);
        while (!q.empty())
        {
            Node<T> *elem = q.front();
            if (func != nullptr)
                func(elem->_data);
            else
                std::cout << *elem->_data;
            q.pop();
            if (elem->_left != nullptr)
                q.push(elem->_left);
            if (elem->_right != nullptr)
                q.push(elem->_right);
        }
    }
}

#endif /* BINARY_SEARCH_TREE_H */
