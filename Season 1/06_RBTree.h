#ifndef RB_TREE_H
#define RB_TREE_H
#include "./06_BBST.h"
// 红黑树
template <typename T>
class RBTree : public BBST<T>
{
    friend std::ostream &operator<<(std::ostream &os, const RBTree<T> &tree) { return draw_tree(os, tree); }

private:
    static const bool BLACK = false;
    static const bool RED = true;
    template <typename U>
    struct RBNode : public RBTree::template Node<U>
    {
        friend std::ostream &operator<<(std::ostream &os, const RBNode<U> &node) 
        {  
            os << *node._data << " ";
            if (node._color)
                return os << "Red";
            else 
                return os << "Black";
        }
        bool _color = RED;
        RBNode(std::shared_ptr<U> data, RBNode<T> *parent = nullptr, RBNode<T> *left = nullptr, RBNode<T> *right = nullptr)
            : RBTree::template Node<U>(data, parent, left, right) {}
        ~RBNode() { this->_data = nullptr; }
    };
    static std::ostream &draw_tree(std::ostream &os, const RBTree<T> &tree);
    void after_add(typename RBTree::template Node<T> *node) override;
    void after_remove(typename RBTree::template Node<T> *node) override;
    RBNode<T> *set_color(RBNode<T> *node, bool color);
    bool color_of(RBNode<T> *node) { return node == nullptr ? BLACK : node->_color; }
    bool is_black(RBNode<T> *node) { return color_of(node) == BLACK; }
    bool is_red(RBNode<T> *node) { return color_of(node) == RED; }

public:
    RBTree(/* args */) = default;
    ~RBTree() = default;
    typename RBTree::template Node<T> *create_node(std::shared_ptr<T> data, typename RBTree::template Node<T> *parent) override { return new RBNode<T>(data, (RBNode<T> *)parent); }
    RBNode<T> *get_node(std::shared_ptr<T> data) const;
};

template <typename T>
inline std::ostream &RBTree<T>::draw_tree(std::ostream &os, const RBTree<T> &tree)
{
    if (tree._root != nullptr)
    {
        size_t height = 0;
        size_t level_count = 1;
        std::queue<RBNode<T> *> q = std::queue<RBNode<T> *>();
        q.push((RBNode<T> *)tree._root);
        while (!q.empty())
        {
            RBNode<T> *elem = q.front();
            if (elem != nullptr)
                os << *tree.get_node(elem->_data) << "\t";
            q.pop();
            if (elem != nullptr)
                q.push((RBNode<T> *)elem->_left);
            if (elem != nullptr)
                q.push((RBNode<T> *)elem->_right);
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
inline RBTree<T>::RBNode<T> *RBTree<T>::set_color(RBNode<T> *node, bool color)
{
    if (node == nullptr)
        return node;
    node->_color = color;
    return node;
}

template <typename T>
inline void RBTree<T>::after_add(typename RBTree::template Node<T> *node)
{
    RBNode<T> *parent = (RBNode<T> *)node->_parent;
    if (parent == nullptr)
    {
        set_color((RBNode<T> *)node, BLACK);
        return;
    }
    if (is_black(parent))
        return;
    RBNode<T> *uncle = (RBNode<T> *)parent->get_sibling();
    RBNode<T> *grand = set_color((RBNode<T> *)parent->_parent, RED);
    if (is_red(uncle))
    {
        set_color(parent, BLACK);
        set_color(uncle, BLACK);
        after_add(grand);
        return;
    }

    if (parent->is_left())
    {
        if (node->is_left())
            set_color(parent, BLACK);
        else
        {
            set_color((RBNode<T> *)node, BLACK);
            this->rotate_left(parent);
        }
        this->rotate_right(grand);
    }
    else
    {
        if (node->is_left())
        {
            set_color((RBNode<T> *)node, BLACK);
            this->rotate_right(parent);
        }
        else
            set_color(parent, BLACK);
        this->rotate_left(grand);
    }
}

template <typename T>
inline void RBTree<T>::after_remove(typename RBTree::template Node<T> *node)
{
}

template <typename T>
inline RBTree<T>::RBNode<T> *RBTree<T>::get_node(std::shared_ptr<T> data) const
{
    typename RBTree<T>::template Node<T> *node = this->_root;
    while (node != nullptr)
    {
        if (*node->_data < *data)
            node = node->_right;
        else if (*node->_data > *data)
            node = node->_left;
        else
            return (typename RBTree<T>::template RBNode<T> *)node;
    }
    return nullptr;
}

#endif
