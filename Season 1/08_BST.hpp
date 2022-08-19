#ifndef BST_HPP
#define BST_HPP

#include "./08_IBinaryTree.hpp"

namespace app {
/**
 * @brief 二叉搜索树基类
 * @date 2022-04-09
 * @tparam T
 */
template <typename T> class BST : public IBinaryTree<T> {
  using NODE = typename IBinaryTree<T>::template Node<T>;

protected:
  virtual void after_add(NODE *node) {}

  virtual void after_remove(NODE *node) {}

  NODE *get_node(shared_ptr<T> data) const override;

public:
  BST<T> &operator=(const BST<T> &tree);

  BST<T> &operator=(BST<T> &&tree) noexcept;

  BST(typename IBinaryTree<T>::Comparator comparator = nullptr)
      : IBinaryTree<T>(comparator) {}

  BST(const BST<T> &tree) { *this = tree; }

  BST(BST<T> &&tree) noexcept { *this = move(tree); }

  virtual ~BST() = default;

  void add(shared_ptr<T> data) override;

  void remove(shared_ptr<T> data) override;
};

template <typename T> inline BST<T> &BST<T>::operator=(const BST<T> &tree) {
  this->clear();
  if (tree._size > 0) {
    this->_comparator = tree._comparator;
    queue<NODE *> q;
    q.push(tree._root);
    while (!q.empty()) {
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

template <typename T> inline BST<T> &BST<T>::operator=(BST<T> &&tree) noexcept {
  this->clear();
  this->_size = tree._size;
  this->_root = tree._root;
  this->_comparator = tree._comparator;
  tree._size = 0;
  tree._root = nullptr;
  tree._comparator = nullptr;
  return *this;
}

template <typename T> inline void BST<T>::add(shared_ptr<T> data) {
  this->not_null_check(data);
  if (this->_root == nullptr) {
    this->_size++;
    this->_root = this->create_node(data, nullptr);
    this->after_add(this->_root);
    return;
  }
  NODE *node = this->_root, *parent = this->_root;
  while (node != nullptr) {
    parent = node; // 找到父结点
    if (this->_comparator == nullptr) {
      if (*node->_data < *data)
        node = node->_right;
      else if (*node->_data > *data)
        node = node->_left;
      else {
        node->_data = data; // 遇到值相等的结点, 覆盖旧值
        return;
      }
    } else {
      if (this->_comparator(node->_data, data) < 0)
        node = node->_right;
      else if (this->_comparator(node->_data, data) > 0)
        node = node->_left;
      else {
        node->_data = data;
        return;
      }
    }
  }
  // 添加新结点
  NODE *temp = this->create_node(data, parent);
  if (this->_comparator == nullptr) {
    if (*parent->_data < *data)
      parent->_right = temp;
    else
      parent->_left = temp;
  } else {
    if (this->_comparator(parent->_data, data) < 0)
      parent->_right = temp;
    else
      parent->_left = temp;
  }
  this->_size++;
  this->after_add(temp);
}

template <typename T> inline void BST<T>::remove(shared_ptr<T> data) {
  NODE *node = get_node(data);
  if (node != nullptr) {
    this->_size--;
    // 删除度为2的结点, 先用前驱/后继覆盖待删结点的值, 然后删除前驱/后继
    if (node->is_binary()) {
      NODE *s = this->get_successor(node);
      node->_data = s->_data;
      node = s;
    }
    // 实际删除的结点度必为0或1
    NODE *replace = node->_left != nullptr ? node->_left : node->_right;
    if (replace != nullptr) {
      replace->_parent = node->_parent;
      if (node->_parent == nullptr)
        this->_root = replace;
      else if (node == node->_parent->_left)
        node->_parent->_left = replace;
      else
        node->_parent->_right = replace;
      this->after_remove(replace); // 度为1, 用子结点替代待删结点
    } else if (node->_parent != nullptr) {
      if (node == node->_parent->_left)
        node->_parent->_left = nullptr;
      else
        node->_parent->_right = nullptr;
      this->after_remove(node);
    } else {
      this->_root = nullptr;
      this->after_remove(node);
    }
    delete node;
  }
}

template <typename T>
inline typename BST<T>::NODE *BST<T>::get_node(shared_ptr<T> data) const {
  NODE *node = this->_root;
  while (node != nullptr) {
    if (this->_comparator == nullptr) {
      if (*node->_data < *data)
        node = node->_right;
      else if (*node->_data > *data)
        node = node->_left;
      else
        return node;
    } else {
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
} // namespace app

#endif /* BST_HPP */
