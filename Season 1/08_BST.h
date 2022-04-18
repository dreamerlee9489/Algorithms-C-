#ifndef BST_H
#define BST_H
#include "./08_IBinaryTree.h"
/**
 * @brief 二叉搜索树基类
 * @date 2022-04-09
 * @tparam T
 */
template <typename T>
class BST : public IBinaryTree<T>
{
    using NODE = typename IBinaryTree<T>::template Node<T>;

protected:
    virtual void after_add(NODE *node) {}
    virtual void after_remove(NODE *node) {}
    NODE *get_node(std::shared_ptr<T> data) const override;

public:
    BST<T> &operator=(const BST<T> &tree);
    BST<T> &operator=(BST<T> &&tree) noexcept;
    BST(typename IBinaryTree<T>::Comparator comparator = nullptr) : IBinaryTree<T>(comparator) {}
    BST(const BST<T> &tree) { *this = tree; }
    BST(BST<T> &&tree) noexcept { *this = std::move(tree); }
    virtual ~BST() = default;
    void add(std::shared_ptr<T> data) override;
    void remove(std::shared_ptr<T> data) override;
};

template <typename T>
inline BST<T> &BST<T>::operator=(const BST<T> &tree)
{
    this->clear();
    if (tree._size > 0)
    {
        this->_comparator = tree._comparator;
        std::queue<NODE *> q = std::queue<NODE *>();
        q.push(tree._root);
        while (!q.empty())
        {
            NODE *elem = q.front();
            add(elem->_data);
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
inline BST<T> &BST<T>::operator=(BST<T> &&tree) noexcept
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
    NODE *node = this->_root, *parent = this->_root;
    while (node != nullptr)
    {
        parent = node;
        if(this->_comparator == nullptr)
        {
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
        else
        {
            if (this->_comparator(node->_data, data) < 0)
                node = node->_right;
            else if (this->_comparator(node->_data, data) > 0)
                node = node->_left;
            else
            {
                node->_data = data;
                return;
            }
        }
    }
    NODE *temp = this->create_node(data, parent);
    if(this->_comparator == nullptr)
    {
        if (*parent->_data < *data)
            parent->_right = temp;
        else
            parent->_left = temp;
    }
    else
    {
        if (this->_comparator(parent->_data, data) < 0)
            parent->_right = temp;
        else
            parent->_left = temp;
    }
    this->_size++;
    this->after_add(temp);
}

template <typename T>
inline void BST<T>::remove(std::shared_ptr<T> data)
{
    NODE *node = get_node(data);
    if (node != nullptr)
    {
        this->_size--;
        if (node->is_binary())
        {
            NODE *s = this->get_successor(node);
            node->_data = s->_data;
            node = s; //删除前驱结点
        }
        NODE *replace = node->_left != nullptr ? node->_left : node->_right;
        if (replace != nullptr)
        {
            replace->_parent = node->_parent;
            if (node->_parent == nullptr)
                this->_root = replace;
            else if (node == node->_parent->_left)
                node->_parent->_left = replace;
            else
                node->_parent->_right = replace;
            this->after_remove(replace);
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
}

template <typename T>
inline typename BST<T>::NODE *BST<T>::get_node(std::shared_ptr<T> data) const
{
    NODE *node = this->_root;
    while (node != nullptr)
    {
        if (this->_comparator == nullptr)
        {
            if (*node->_data < *data)
                node = node->_right;
            else if (*node->_data > *data)
                node = node->_left;
            else
                return node;
        }
        else
        {
            if (this->_comparator(node->_data, data) < 0)
                node = node->_right;
            else if (this->_comparator(node->_data, data) > 0)
                node = node->_left;
            else
                return node;
        }
    }
    return nullptr;
}

#endif /* BST_H */
