#ifndef BST_H
#define BST_H
#include "./06_IBinaryTree.h"
// 二叉搜索树
template <typename T>
class BST : public IBinaryTree<T>
{
    friend std::ostream &operator<<(std::ostream &os, const BST<T> &tree) { return draw_tree(os, tree); }

private:
    static std::ostream &draw_tree(std::ostream &os, const BST<T> &tree);

public:
    BST() = default;
    ~BST() { this->clear_recu(this->_root); }
    typename BST::template Node<T> *get_node(std::shared_ptr<T> data) const override;
    void add(std::shared_ptr<T> data) override;
    void remove(std::shared_ptr<T> data) override;
};

template <typename T>
std::ostream &BST<T>::draw_tree(std::ostream &os, const BST<T> &tree)
{
    if (tree._root == nullptr)
        return os;
    size_t height = 0, total_height = tree.height();
    size_t level_count = 1;
    size_t str_size = 16;
    size_t width = std::pow(2, total_height - 1) * str_size;
    std::queue<typename BST::template Node<T> *> q = std::queue<typename BST::template Node<T> *>();
    q.push(tree._root);
    while (!q.empty())
    {
        size_t space = width / std::pow(2, height + 1) - str_size / 2;
        typename BST::template Node<T> *elem = q.front();
        std::string str;
        if (elem != nullptr)
            str = std::string(space, ' ') + ((IString &)*elem->_data).to_string() + std::string(space, ' ');
        else
            str = std::string(str_size, ' ');
        os << str;
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
    return os;
}

template <typename T>
void BST<T>::add(std::shared_ptr<T> data)
{
    this->not_null_check(data);
    if (this->_root == nullptr)
    {
        this->_root = new typename BST::template Node<T>(data);
        this->_size++;
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
    typename BST::template Node<T> *temp = new typename BST::template Node<T>(data, parent);
    if (*data > *parent->_data)
        parent->_right = temp;
    else
        parent->_left = temp;
    this->_size++;
}

template <typename T>
void BST<T>::remove(std::shared_ptr<T> data)
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
    }
    else if (node->_parent != nullptr)
    {
        if (node == node->_parent->_left)
            node->_parent->_left = nullptr;
        else
            node->_parent->_right = nullptr;
    }
    else
        this->_root = nullptr;
    delete node;
}

template <typename T>
typename BST<T>::BST::template Node<T> *BST<T>::get_node(std::shared_ptr<T> data) const
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
