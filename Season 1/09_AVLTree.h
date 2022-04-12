#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "./08_BBST.h"
// AVL树
template <typename T>
class AVLTree : public BBST<T>
{
    using BTNode = typename BBST<T>::template Node<T>;
    friend std::ostream &operator<<(std::ostream &os, const AVLTree<T> &tree) { return draw_tree(os, tree); }

private:
    template <typename U>
    struct AVLNode : public AVLTree::template Node<U>
    {
        friend std::ostream &operator<<(std::ostream &os, const AVLNode<U> &node) { return os << *node._data << " h:" << node._height; }
        size_t _height = 1;
        AVLNode(std::shared_ptr<U> data, AVLNode<T> *parent = nullptr, AVLNode<T> *left = nullptr, AVLNode<T> *right = nullptr)
            : AVLTree::template Node<U>(data, parent, left, right) {}
        ~AVLNode() = default;
        int balance_factor();
        void update_height();
        AVLNode<U> *taller_child();
    };
    static std::ostream &draw_tree(std::ostream &os, const AVLTree<T> &tree);
    void rotate(BTNode *r, BTNode *b, BTNode *c, BTNode *d, BTNode *e, BTNode *f) override;
    void after_rotate(BTNode *grand, BTNode *parent, BTNode *child) override;
    void after_add(BTNode *node) override;
    void after_remove(BTNode *node) override;
    bool is_balanced(AVLNode<T> *node) { return std::abs(node->balance_factor()) <= 1; }
    void update_height(AVLNode<T> *node) { node->update_height(); }
    void rebalance(AVLNode<T> *grand);

public:
    AVLTree() = default;
    ~AVLTree() = default;
    BTNode *create_node(std::shared_ptr<T> data, BTNode *parent) override { return new AVLNode<T>(data, (AVLNode<T> *)parent); }
    AVLNode<T> *get_node(std::shared_ptr<T> data) const;
};

template <typename T>
inline std::ostream &AVLTree<T>::draw_tree(std::ostream &os, const AVLTree<T> &tree)
{
    if (tree._root != nullptr)
    {
        size_t height = 0;
        size_t level_count = 1;
        std::queue<AVLNode<T> *> q = std::queue<AVLNode<T> *>();
        q.push((AVLNode<T> *)tree._root);
        while (!q.empty())
        {
            AVLNode<T> *elem = q.front();
            if (elem != nullptr)
                os << *tree.get_node(elem->_data) << "\t";
            q.pop();
            if (elem != nullptr)
                q.push((AVLNode<T> *)elem->_left);
            if (elem != nullptr)
                q.push((AVLNode<T> *)elem->_right);
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
inline void AVLTree<T>::after_add(BTNode *node)
{
    while ((node = node->_parent) != nullptr)
    {
        if (is_balanced((AVLNode<T> *)node))
            update_height((AVLNode<T> *)node);
        else
        {
            rebalance((AVLNode<T> *)node);
            break;
        }
    }
}

template <typename T>
inline void AVLTree<T>::after_remove(BTNode *node)
{
    while ((node = node->_parent) != nullptr)
    {
        if (is_balanced((AVLNode<T> *)node))
            update_height((AVLNode<T> *)node);
        else
            rebalance((AVLNode<T> *)node);
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
inline void AVLTree<T>::rebalance(AVLNode<T> *grand)
{
    AVLNode<T> *parent = grand->taller_child();
    AVLNode<T> *node = parent->taller_child();
    if (parent->is_left())
    {
        if (node->is_left())
        {
            this->rotate_right(grand);
            // rotate(grand, node, (AVLNode<T> *)node->_right, parent, (AVLNode<T> *)parent->_right, grand);
        }
        else
        {
            this->rotate_left(parent);
            this->rotate_right(grand);
            // rotate(grand, parent, (AVLNode<T> *)node->_left, node, (AVLNode<T> *)node->_right, grand);
        }
    }
    else
    {
        if (node->is_left())
        {
            this->rotate_right(parent);
            this->rotate_left(grand);
            // rotate(grand, parent, (AVLNode<T> *)node->_left, node, (AVLNode<T> *)node->_right, parent);
        }
        else
        {
            this->rotate_left(grand);
            // rotate(grand, grand, (AVLNode<T> *)parent->_left, parent, (AVLNode<T> *)node->_left, node);
        }
    }
}

template <typename T>
void AVLTree<T>::rotate(BTNode *r, BTNode *b, BTNode *c, BTNode *d, BTNode *e, BTNode *f)
{
    BBST<T>::rotate(r, b, c, d, e, f);
    update_height((AVLNode<T> *)b);
    update_height((AVLNode<T> *)f);
    update_height((AVLNode<T> *)d);
}

template <typename T>
void AVLTree<T>::after_rotate(BTNode *grand, BTNode *parent, BTNode *child)
{
    BBST<T>::after_rotate(grand, parent, child);
    update_height((AVLNode<T> *)grand);
    update_height((AVLNode<T> *)parent);
}

template <typename T>
inline AVLTree<T>::AVLNode<T> *AVLTree<T>::get_node(std::shared_ptr<T> data) const
{
    typename AVLTree<T>::template Node<T> *node = this->_root;
    while (node != nullptr)
    {
        if (*node->_data < *data)
            node = node->_right;
        else if (*node->_data > *data)
            node = node->_left;
        else
            return (AVLNode<T> *)node;
    }
    return nullptr;
}

#endif /* AVL_TREE_H */