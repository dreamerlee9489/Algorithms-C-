#ifndef BST_H
#define BST_H
#include "./06_IBinaryTree.h"
// 二叉搜索树
template <typename T>
class BST : public IBinaryTree<T>
{
protected:
    virtual void after_add(typename BST::template Node<T> *node) {}
    virtual void after_remove(typename BST::template Node<T> *node) {}

public:
    BST() = default;
    ~BST() { this->clear_recu(this->_root); }
    typename BST::template Node<T> *get_node(std::shared_ptr<T> data) const override;
    void add(std::shared_ptr<T> data) override;
    void remove(std::shared_ptr<T> data) override;
};

template <typename T>
inline void BST<T>::add(std::shared_ptr<T> data)
{
    this->not_null_check(data);
    if (this->_root == nullptr)
    {
        this->_root = this->create_node(data, nullptr);
        this->_size++;
        this->after_add(this->_root);
        return;
    }
    typename BST::template Node<T> *node = this->_root, *parent = this->_root;
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
    typename BST::template Node<T> *temp = this->create_node(data, parent);
    if (*data > *parent->_data)
        parent->_right = temp;
    else
        parent->_left = temp;
    this->_size++;
    this->after_add(temp);
}

template <typename T>
inline void BST<T>::remove(std::shared_ptr<T> data)
{
    this->_size--;
    typename BST::template Node<T> *node = get_node(data);
    if (node == nullptr)
        return;
    if (node->is_binary())
    {
        typename BST::template Node<T> *s = this->get_successor(node);
        node->_data = s->_data;
        node = s; //删除前驱结点
    }
    typename BST::template Node<T> *replace = node->_left != nullptr ? node->_left : node->_right;
    if (replace != nullptr)
    {
        replace->_parent = node->_parent;
        if (node->_parent == nullptr)
            this->_root = replace;
        else if (node == node->_parent->_left)
            node->_parent->_left = replace;
        else
            node->_parent->_right = replace;
        this->after_remove(node);
    }
    else if (node->_parent != nullptr)
    {
        if (node == node->_parent->_left)
            node->_parent->_left = nullptr;
        else
            node->_parent->_right = nullptr;
        this->after_remove(node);
    }
    else
    {
        this->_root = nullptr;
        this->after_remove(node);
    }
    delete node;
}

template <typename T>
inline typename BST<T>::BST::template Node<T> *BST<T>::get_node(std::shared_ptr<T> data) const
{
    typename BST::template Node<T> *node = this->_root;
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

#endif /* BST_H */
