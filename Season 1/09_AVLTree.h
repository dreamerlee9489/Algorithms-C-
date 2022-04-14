#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "./08_BBST.h"
// AVL树
template <typename T>
class AVLTree : public BBST<T>
{
    using NODE = typename BBST<T>::template Node<T>;
    friend std::ostream &operator<<(std::ostream &os, const AVLTree<T> &tree) { return draw_tree(os, tree); }

private:
    template <typename U>
    struct AVLNode : public NODE
    {
        size_t _height = 1;
        AVLNode<U> &operator=(const AVLNode<U> &node);
        AVLNode<U> &operator=(AVLNode<U> &&node);
        AVLNode(std::shared_ptr<U> data, NODE *parent = nullptr, NODE *left = nullptr, NODE *right = nullptr)
            : NODE(data, parent, left, right) {}
        ~AVLNode() = default;
        AVLNode(const AVLNode<U> &node) { *this = node; }
        AVLNode(AVLNode<U> &&node) { *this = std::move(node); }
        int balance_factor();
        void update_height();
        NODE *taller_child();
        std::string to_string() const override { return ((IString &)*this->_data).to_string() + " h=" + std::to_string(_height); }
    };
    static std::ostream &draw_tree(std::ostream &os, const AVLTree<T> &tree);
    void rotate(NODE *r, NODE *b, NODE *c, NODE *d, NODE *e, NODE *f) override;
    void after_rotate(NODE *grand, NODE *parent, NODE *child) override;
    void after_add(NODE *node) override;
    void after_remove(NODE *node) override;
    bool is_balanced(NODE *node) { return std::abs(((AVLNode<T> *)node)->balance_factor()) <= 1; }
    void update_height(NODE *node) { ((AVLNode<T> *)node)->update_height(); }
    void rebalance(NODE *grand);

public:
    AVLTree<T> &operator=(const AVLTree<T> &tree);
    AVLTree<T> &operator=(AVLTree<T> &&tree);
    AVLTree() = default;
    ~AVLTree() = default;
    AVLTree(const AVLTree<T> &tree) { *this = tree; }
    AVLTree(AVLTree &&tree) { *this = std::move(tree); }
    NODE *create_node(std::shared_ptr<T> data, NODE *parent) override { return new AVLNode<T>(data, parent); }
    AVLNode<T> *get_node(std::shared_ptr<T> data) const;
};

template <typename T>
template <typename U>
inline AVLTree<T>::AVLNode<U> &AVLTree<T>::AVLNode<U>::operator=(const AVLNode<U> &node)
{
    this->_data = node._data;
    this->_parent = node._parent;
    this->_left = node._left;
    this->_right = node._right;
    _height = node._height;
    return *this;
}

template <typename T>
template <typename U>
inline AVLTree<T>::AVLNode<U> &AVLTree<T>::AVLNode<U>::operator=(AVLNode<U> &&node)
{
    this->_data = std::move(node._data);
    this->_parent = std::move(node._parent);
    this->_left = std::move(node._left);
    this->_right = std::move(node._right);
    _height = std::move(node._height);
    return *this;
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
inline typename AVLTree<T>::NODE *AVLTree<T>::AVLNode<U>::taller_child()
{
    size_t leftH = (this->_left == nullptr) ? 0 : ((AVLNode<U> *)this->_left)->_height;
    size_t rightH = (this->_right == nullptr) ? 0 : ((AVLNode<U> *)this->_right)->_height;
    if (leftH > rightH)
        return this->_left;
    if (leftH < rightH)
        return this->_right;
    return this->is_left() ? this->_left : this->_right;
}

template <typename T>
inline AVLTree<T> &AVLTree<T>::operator=(const AVLTree<T> &tree)
{
    this->clear();
    if (tree._size > 0)
    {
        std::queue<NODE *> q = std::queue<NODE *>();
        q.push(tree._root);
        while (!q.empty())
        {
            NODE *elem = q.front();
            this->add(elem->_data);
            q.pop();
            if (elem->_left != nullptr)
                q.push(elem->_left);
            if (elem->_right != nullptr)
                q.push(elem->_right);
        }
    }
    return *this;
}

template <typename T>
inline AVLTree<T> &AVLTree<T>::operator=(AVLTree<T> &&tree)
{
    this->clear();
    this->_root = tree._root;
    this->_size = tree._size;
    tree._root = nullptr;
    tree._size = 0;
    return *this;
}

template <typename T>
inline std::ostream &AVLTree<T>::draw_tree(std::ostream &os, const AVLTree<T> &tree)
{
    if (tree._root != nullptr)
    {
        size_t height = 0;
        size_t level_count = 1;
        std::queue<NODE *> q = std::queue<NODE *>();
        q.push(tree._root);
        while (!q.empty())
        {
            NODE *elem = q.front();
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
inline void AVLTree<T>::after_add(NODE *node)
{
    while ((node = node->_parent) != nullptr)
    {
        if (is_balanced(node))
            update_height(node);
        else
        {
            rebalance(node);
            break;
        }
    }
}

template <typename T>
inline void AVLTree<T>::after_remove(NODE *node)
{
    while ((node = node->_parent) != nullptr)
    {
        if (is_balanced(node))
            update_height(node);
        else
            rebalance(node);
    }
}

template <typename T>
inline void AVLTree<T>::rebalance(NODE *grand)
{
    NODE *parent = ((AVLNode<T> *)grand)->taller_child();
    NODE *node = ((AVLNode<T> *)parent)->taller_child();
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
inline void AVLTree<T>::rotate(NODE *r, NODE *b, NODE *c, NODE *d, NODE *e, NODE *f)
{
    BBST<T>::rotate(r, b, c, d, e, f);
    update_height(b);
    update_height(f);
    update_height(d);
}

template <typename T>
inline void AVLTree<T>::after_rotate(NODE *grand, NODE *parent, NODE *child)
{
    BBST<T>::after_rotate(grand, parent, child);
    update_height(grand);
    update_height(parent);
}

template <typename T>
inline AVLTree<T>::AVLNode<T> *AVLTree<T>::get_node(std::shared_ptr<T> data) const
{
    NODE *node = this->_root;
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