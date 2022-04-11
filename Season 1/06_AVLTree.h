#ifndef AVL_TREE_h
#define AVL_TREE_h
#include "./06_BST.h"
// 平衡二叉搜索树
template <typename T>
class AVLTree : public BST<T>
{
private:
    template <typename U>
    struct AVLNode : public AVLTree::template Node<U>
    {
        size_t _height = 1;
        AVLNode(std::shared_ptr<U> data, AVLNode<T> *parent = nullptr, AVLNode<T> *left = nullptr, AVLNode<T> *right = nullptr)
            : AVLTree::template Node<U>(data, parent, left, right) {}
        ~AVLNode() { this->_data = nullptr; }
        int balance_factor();
        void update_height();
        AVLNode<U> *taller_child();
    };
    void after_add(typename AVLTree::template Node<T> *node) override;
    void after_remove(typename AVLTree::template Node<T> *node) override;
    bool is_balanced(AVLNode<T> *node) { return std::abs(node->balance_factor()) <= 1; }
    void update_height(AVLNode<T> *node) { node->update_height(); }
    void rebalance0(AVLNode<T> *grand);
    void rebalance1(AVLNode<T> *grand);
    void rotate(AVLNode<T> *r, AVLNode<T> *b, AVLNode<T> *c, AVLNode<T> *d, AVLNode<T> *e, AVLNode<T> *f);
    void rotate_left(AVLNode<T> *grand);
    void rotate_right(AVLNode<T> *grand);
    void after_rotate(AVLNode<T> *grand, AVLNode<T> *parent, AVLNode<T> *child);

public:
    AVLTree() = default;
    ~AVLTree() = default;
    typename AVLTree::template Node<T> *create_node(std::shared_ptr<T> data, typename AVLTree::template Node<T> *parent) override
    {
        return new AVLNode<T>(data, (AVLNode<T> *)parent);
    }
};

template <typename T>
inline void AVLTree<T>::after_add(typename AVLTree::template Node<T> *node)
{
    while ((node = node->_parent) != nullptr)
    {
        if (is_balanced((AVLNode<T> *)node))
            update_height((AVLNode<T> *)node);
        else
        {
            rebalance0((AVLNode<T> *)node);
            break;
        }
    }
}

template <typename T>
inline void AVLTree<T>::after_remove(typename AVLTree::template Node<T> *node)
{
    while ((node = node->_parent) != nullptr)
    {
        if (is_balanced((AVLNode<T> *)node))
            update_height((AVLNode<T> *)node);
        else
            rebalance0((AVLNode<T> *)node);
    }
}

template <typename T>
template <typename U>
inline int AVLTree<T>::AVLNode<U>::balance_factor()
{
    size_t leftH = (this->_left == nullptr) ? 0 : ((AVLNode<U> *)this->_left)->_height;
    size_t rightH = (this->_right == nullptr) ? 0 : ((AVLNode<U> *)this->_right)->_height;
    return (int)(leftH - rightH);
}

template <typename T>
template <typename U>
inline void AVLTree<T>::AVLNode<U>::update_height()
{
    size_t leftH = (this->_left == nullptr) ? 0 : ((AVLNode<U> *)this->_left)->_height;
    size_t rightH = (this->_right == nullptr) ? 0 : ((AVLNode<U> *)this->_right)->_height;
    _height = 1 + std::max(leftH, rightH);
}

template <typename T>
template <typename U>
inline typename AVLTree<T>::template AVLNode<U> *AVLTree<T>::AVLNode<U>::taller_child()
{
    size_t leftH = (this->_left == nullptr) ? 0 : ((AVLNode<U> *)this->_left)->_height;
    size_t rightH = (this->_right == nullptr) ? 0 : ((AVLNode<U> *)this->_right)->_height;
    if (leftH > rightH)
        return (AVLNode<U> *)this->_left;
    if (leftH < rightH)
        return (AVLNode<U> *)this->_right;
    return this->is_left() ? (AVLNode<U> *)this->_left : (AVLNode<U> *)this->_right;
}

template <typename T>
inline void AVLTree<T>::rebalance0(AVLNode<T> *grand)
{
    AVLNode<T> *parent = grand->taller_child();
    AVLNode<T> *node = parent->taller_child();
    if (parent->is_left())
    {
        if (node->is_left())
            rotate(grand, node, (AVLNode<T> *)node->_right, parent, (AVLNode<T> *)parent->_right, grand);
        else
            rotate(grand, parent, (AVLNode<T> *)node->_left, node, (AVLNode<T> *)node->_right, grand);
    }
    else
    {
        if (node->is_left())
            rotate(grand, parent, (AVLNode<T> *)node->_left, node, (AVLNode<T> *)node->_right, parent);
        else
            rotate(grand, grand, (AVLNode<T> *)parent->_left, parent, (AVLNode<T> *)node->_left, node);
    }
}

template <typename T>
inline void AVLTree<T>::rebalance1(AVLNode<T> *grand)
{
    AVLNode<T> *parent = grand->taller_child();
    AVLNode<T> *node = parent->taller_child();
    if (parent->is_left())
    {
        if (node->is_left())
            rotate_right(grand);
        else
        {
            rotate_left(parent);
            rotate_right(grand);
        }
    }
    else
    {
        if (node->is_left())
        {
            rotate_right(parent);
            rotate_left(grand);
        }
        else
            rotate_left(grand);
    }
}

template <typename T>
inline void AVLTree<T>::rotate(AVLNode<T> *r, AVLNode<T> *b, AVLNode<T> *c, AVLNode<T> *d, AVLNode<T> *e, AVLNode<T> *f)
{
    d->_parent = r->_parent;
    if (r->is_left())
        r->_parent->_left = d;
    else if (r->is_right())
        r->_parent->_right = d;
    else
        this->_root = d;

    b->_right = c;
    if (c != nullptr)
        c->_parent = b;
    update_height(b);

    f->_left = e;
    if (e != nullptr)
        e->_parent = f;
    update_height(f);

    d->_left = b;
    d->_right = f;
    b->_parent = d;
    f->_parent = d;
    update_height(d);
}

template <typename T>
inline void AVLTree<T>::rotate_left(AVLNode<T> *grand)
{
    AVLNode<T> *parent = (AVLNode<T> *)grand->_right;
    AVLNode<T> *child = (AVLNode<T> *)parent->_left;
    grand->_right = child;
    parent->_left = grand;
    after_rotate(grand, parent, child);
}

template <typename T>
inline void AVLTree<T>::rotate_right(AVLNode<T> *grand)
{
    AVLNode<T> *parent = (AVLNode<T> *)grand->_left;
    AVLNode<T> *child = (AVLNode<T> *)parent->_right;
    grand->_left = child;
    parent->_right = grand;
    after_rotate(grand, parent, child);
}

template <typename T>
inline void AVLTree<T>::after_rotate(AVLNode<T> *grand, AVLNode<T> *parent, AVLNode<T> *child)
{
    parent->_parent = grand->_parent;
    if (grand->is_left())
        grand->_parent->_left = parent;
    else if (grand->is_right())
        grand->_parent->_right = parent;
    else
        this->_root = parent;

    if (child != nullptr)
        child->_parent = grand;

    grand->_parent = parent;
    update_height(grand);
    update_height(parent);
}

#endif /* AVL_TREE_h */