#ifndef RB_TREE_HPP
#define RB_TREE_HPP
#include "./08_BBST.hpp"

namespace app
{
    /**
     * @brief 红黑树
     * @date 2022-04-13
     * @tparam T
     */
    template <typename T>
    class RBTree : public BBST<T>
    {
        using NODE = typename IBinaryTree<T>::template Node<T>;
        static const bool BLACK = false, RED = true;
        template <typename U>
        struct RBNode : public NODE
        {
            bool _color = RED;
            RBNode<U> &operator=(const RBNode<U> &node);
            RBNode<U> &operator=(RBNode<U> &&node) noexcept;
            RBNode(shared_ptr<U> data, NODE *parent = nullptr, NODE *left = nullptr, NODE *right = nullptr)
                : NODE(data, parent, left, right) {}
            RBNode(const RBNode<U> &node) { *this = node; }
            RBNode(RBNode<U> &&node) noexcept { *this = move(node); }
            ~RBNode() = default;
            string to_string() const override
            {
                string str = ((IString &)*this->_data).to_string();
                return str += _color == RED ? " R E D" : " BLACK";
            }
        };
        RBNode<T> *get_node(shared_ptr<T> data) const override { return (RBNode<T> *)BBST<T>::get_node(data); }
        NODE *create_node(shared_ptr<T> data, NODE *parent) override { return new RBNode<T>(data, parent); }
        void after_add(NODE *node) override;
        void after_remove(NODE *node) override;
        NODE *set_color(NODE *node, bool color);
        bool color_of(NODE *node) { return node == nullptr ? BLACK : ((RBNode<T> *)node)->_color; }
        bool is_black(NODE *node) { return color_of(node) == BLACK; }
        bool is_red(NODE *node) { return color_of(node) == RED; }

    public:
        RBTree<T> &operator=(const RBTree<T> &tree);
        RBTree<T> &operator=(RBTree<T> &&tree) noexcept;
        RBTree(typename IBinaryTree<T>::Comparator comparator = nullptr) : BBST<T>(comparator) {}
        RBTree(const RBTree<T> &tree) { *this = tree; }
        RBTree(RBTree<T> &&tree) noexcept { *this = move(tree); }
        ~RBTree() = default;
    };

    template <typename T>
    template <typename U>
    inline RBTree<T>::RBNode<U> &RBTree<T>::RBNode<U>::operator=(const RBNode<U> &node)
    {
        this->_data = node._data;
        this->_parent = node._parent;
        this->_left = node._left;
        this->_right = node._right;
        _color = node._color;
        return *this;
    }

    template <typename T>
    template <typename U>
    inline RBTree<T>::RBNode<U> &RBTree<T>::RBNode<U>::operator=(RBNode<U> &&node) noexcept
    {
        this->_data = nullptr;
        this = &node;
        return *this;
    }

    template <typename T>
    inline RBTree<T> &RBTree<T>::operator=(const RBTree<T> &tree)
    {
        this->clear();
        if (tree._size > 0)
        {
            this->_comparator = tree._comparator;
            queue<NODE *> q;
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
    inline RBTree<T> &RBTree<T>::operator=(RBTree<T> &&tree) noexcept
    {
        this->clear();
        this->_size = tree._size;
        this->_root = tree._root;
        this->_comparator = tree._comparator;
        tree._size = 0;
        tree._root = nullptr;
        tree._comparator = nullptr;
        return *this;
    }

    template <typename T>
    inline typename RBTree<T>::NODE *RBTree<T>::set_color(NODE *node, bool color)
    {
        if (node != nullptr)
            ((RBNode<T> *)node)->_color = color;
        return node;
    }

    template <typename T>
    inline void RBTree<T>::after_add(NODE *node)
    {
        NODE *parent = node->_parent;
        if (parent == nullptr)
        {
            set_color(node, BLACK);
            return;
        }
        if (is_red(parent))
        {
            NODE *uncle = parent->get_sibling();
            NODE *grand = set_color(parent->_parent, RED);
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
                    set_color(node, BLACK);
                    this->rotate_left(parent);
                }
                this->rotate_right(grand);
            }
            else
            {
                if (node->is_left())
                {
                    set_color(node, BLACK);
                    this->rotate_right(parent);
                }
                else
                    set_color(parent, BLACK);
                this->rotate_left(grand);
            }
        }
    }

    template <typename T>
    inline void RBTree<T>::after_remove(NODE *node)
    {
        if (is_red(node))
        {
            set_color(node, BLACK);
            return;
        }
        NODE *parent = node->_parent;
        if (parent != nullptr)
        {
            bool is_left = parent->_left == nullptr || node->is_left();
            NODE *sibling = is_left ? parent->_right : parent->_left;
            if (is_left)
            {
                if (is_red(sibling))
                {
                    set_color(sibling, BLACK);
                    set_color(parent, RED);
                    this->rotate_left(parent);
                    sibling = parent->_right;
                }
                if (is_black(sibling->_left) && is_black(sibling->_right))
                {
                    bool parent_black = is_black(parent);
                    set_color(parent, BLACK);
                    set_color(sibling, RED);
                    if (parent_black)
                        after_remove(parent);
                }
                else
                {
                    if (is_black(sibling->_right))
                    {
                        this->rotate_right(sibling);
                        sibling = parent->_right;
                    }
                    set_color(sibling, color_of(parent));
                    set_color(sibling->_right, BLACK);
                    set_color(parent, BLACK);
                    this->rotate_left(parent);
                }
            }
            else
            {
                if (is_red(sibling))
                {
                    set_color(sibling, BLACK);
                    set_color(parent, RED);
                    this->rotate_right(parent);
                    sibling = parent->_left;
                }
                if (is_black(sibling->_left) && is_black(sibling->_right))
                {
                    bool parent_black = is_black(parent);
                    set_color(parent, BLACK);
                    set_color(sibling, RED);
                    if (parent_black)
                        after_remove(parent);
                }
                else
                {
                    if (is_black(sibling->_left))
                    {
                        this->rotate_left(sibling);
                        sibling = parent->_left;
                    }
                    set_color(sibling, color_of(parent));
                    set_color(sibling->_left, BLACK);
                    set_color(parent, BLACK);
                    this->rotate_right(parent);
                }
            }
        }
    }
} // namespace app

#endif /* RB_TREE_HPP */
