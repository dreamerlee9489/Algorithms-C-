#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include "./IString.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <queue>
#include <stack>

using namespace std;

namespace app {
/**
 * @brief 二叉树基类
 * @date 2022-04-10
 * @tparam T
 */
template <typename T> class IBinaryTree {
  friend ostream &operator<<(ostream &os, const IBinaryTree<T> &tree) {
    return draw_tree(os, tree);
  }

protected:
  using TraverseFunc = bool (*)(shared_ptr<T> data);
  using Comparator = int (*)(shared_ptr<T> a, shared_ptr<T> b);

  template <typename U> struct Node : public IString {
    friend ostream &operator<<(ostream &os, const Node<U> &node) {
      return os << node.to_string();
    }

    shared_ptr<U> _data = nullptr;
    Node<U> *_parent = nullptr, *_left = nullptr, *_right = nullptr;

    Node<U> &operator=(const Node<U> &node);

    Node<U> &operator=(Node<U> &&node) noexcept;

    Node(shared_ptr<U> data, Node<U> *parent = nullptr, Node<U> *left = nullptr,
         Node<U> *right = nullptr)
        : _data(data), _parent(parent), _left(left), _right(right) {}

    Node(const Node<U> &node) { *this = node; }

    Node(Node<U> &&node) noexcept { *this = move(node); }

    virtual ~Node() { _data = nullptr; }

    bool is_leaf() const { return _left == nullptr && _right == nullptr; }

    bool is_binary() const { return _left != nullptr && _right != nullptr; }

    bool is_left() const {
      return _parent != nullptr && this == _parent->_left;
    }

    bool is_right() const {
      return _parent != nullptr && this == _parent->_right;
    }

    Node<U> *get_sibling() const;

    string to_string() const override {
      return ((IString &)*_data).to_string();
    }
  };

  size_t _size = 0;
  Comparator _comparator = nullptr;
  Node<T> *_root = nullptr;

  void not_null_check(shared_ptr<T> data) const {
    if (data == nullptr)
      throw invalid_argument("data must be not null.");
  }

  static ostream &draw_tree(ostream &os, const IBinaryTree<T> &tree);

  virtual Node<T> *get_node(shared_ptr<T> data) const = 0;

  virtual Node<T> *create_node(shared_ptr<T> data, Node<T> *parent) {
    return new Node<T>(data, parent);
  }

  Node<T> *get_predecessor(Node<T> *node) const;

  Node<T> *get_successor(Node<T> *node) const;

  void inorder_recu(Node<T> *node, TraverseFunc func) const;

  void preorder_recu(Node<T> *node, TraverseFunc func) const;

  void postorder_recu(Node<T> *node, TraverseFunc func) const;

  void inorder_iter(TraverseFunc func) const;

  void preorder_iter(TraverseFunc func) const;

  void postorder_iter(TraverseFunc func) const;

  void levelorder(Node<T> *node, TraverseFunc func) const;

  void morrisorder(Node<T> *node, TraverseFunc func) const;

  size_t height_recu(Node<T> *node) const {
    if (node != nullptr)
      return 1 + max(height_recu(node->_left), height_recu(node->_right));
    return 0;
  }

  size_t height_iter(Node<T> *node) const;

  void clear_recu(Node<T> *node);

public:
  enum class TraverseOrder { In, Pre, Post, Level, Morris };

  IBinaryTree(Comparator comparator = nullptr) { _comparator = comparator; }

  virtual ~IBinaryTree() { clear_recu(_root); }

  virtual void add(shared_ptr<T> data) = 0;

  virtual void remove(shared_ptr<T> data) = 0;

  size_t size() const { return _size; }

  size_t height() const { return height_iter(_root); }

  bool is_empty() const { return _size == 0; }

  bool is_complete() const;

  bool contains(shared_ptr<T> data) const { return get_node(data) != nullptr; }

  void traverse(TraverseOrder order = TraverseOrder::In,
                TraverseFunc func = nullptr) const;

  void clear() {
    clear_recu(_root);
    _root = nullptr;
    _size = 0;
  }
};

template <typename T>
template <typename U>
inline typename IBinaryTree<T>::template Node<U> &
IBinaryTree<T>::Node<U>::operator=(const IBinaryTree<T>::Node<U> &node) {
  _data = node._data;
  _parent = node._parent;
  _left = node._left;
  _right = node._right;
  return *this;
}

template <typename T>
template <typename U>
inline typename IBinaryTree<T>::template Node<U> &
IBinaryTree<T>::Node<U>::operator=(Node<U> &&node) noexcept {
  _data = nullptr;
  this = &node;
  return *this;
}

template <typename T>
template <typename U>
inline typename IBinaryTree<T>::template Node<U> *
IBinaryTree<T>::Node<U>::get_sibling() const {
  if (is_left())
    return _parent->_right;
  else if (is_right())
    return _parent->_left;
  return nullptr;
}

template <typename T>
inline ostream &IBinaryTree<T>::draw_tree(ostream &os,
                                          const IBinaryTree<T> &tree) {
  if (tree._root != nullptr) {
    size_t height = 0;
    size_t level_count = 1;
    queue<Node<T> *> q;
    q.push(tree._root);
    while (!q.empty()) {
      Node<T> *elem = q.front();
      if (elem != nullptr)
        os << *tree.get_node(elem->_data) << "\t";
      q.pop();
      if (elem != nullptr)
        q.push(elem->_left);
      if (elem != nullptr)
        q.push(elem->_right);
      level_count--;
      if (level_count == 0) {
        level_count = q.size();
        height++;
        os << "\n";
      }
    }
  }
  return os;
}

template <typename T>
inline typename IBinaryTree<T>::template Node<T> *
IBinaryTree<T>::get_predecessor(Node<T> *node) const {
  if (node == nullptr)
    return node;
  // 如果左子树不空, 前驱结点为左子树中最后一个右结点
  if (node->_left != nullptr) {
    Node<T> *pred = node->_left;
    while (pred->_right != nullptr)
      pred = pred->_right;
    return pred;
  }
  // 如果左子树为空, 前驱结点为祖先结点中第一个小于自身的结点
  while (node->_parent != nullptr && node == node->_parent->_left)
    node = node->_parent;
  return node->_parent;
}

template <typename T>
inline typename IBinaryTree<T>::template Node<T> *
IBinaryTree<T>::get_successor(Node<T> *node) const {
  if (node == nullptr)
    return node;
  // 如果右子树不空, 后继结点为右子树中最后一个左结点
  if (node->_right != nullptr) {
    Node<T> *succ = node->_right;
    while (succ->_left != nullptr)
      succ = succ->_left;
    return succ;
  }
  // 如果右子树为空, 后继结点为祖先结点中第一个大于自身的结点
  while (node->_parent != nullptr && node == node->_parent->_right)
    node = node->_parent;
  return node->_parent;
}

template <typename T> inline bool IBinaryTree<T>::is_complete() const {
  if (_root == nullptr)
    return false;
  queue<Node<T> *> q;
  q.push(_root);
  bool leaf = false;
  while (!q.empty()) {
    Node<T> *node = q.front();
    q.pop();
    if (leaf && !node->is_leaf())
      return false;
    // 如果左结点不空, 压入左结点
    // 如果左结点为空, 右结点不空返回false
    if (node->_left != nullptr)
      q.push(node->_left);
    else if (node->_right != nullptr)
      return false;
    // 如果右结点不空, 压入右结点
    // 如果右结点为空, 表示已到达非叶结点, 剩余的结点应全为叶结点
    if (node->_right != nullptr)
      q.push(node->_right);
    else
      leaf = true;
  }
  return true;
}

template <typename T> inline void IBinaryTree<T>::clear_recu(Node<T> *node) {
  if (node != nullptr) {
    clear_recu(node->_left);
    clear_recu(node->_right);
    delete node;
  }
}

template <typename T>
inline size_t IBinaryTree<T>::height_iter(Node<T> *node) const {
  size_t height = 0;
  if (node != nullptr) {
    queue<Node<T> *> q;
    q.push(node);
    size_t count = 1;
    while (!q.empty()) {
      Node<T> *elem = q.front();
      q.pop();
      if (elem->_left != nullptr)
        q.push(elem->_left);
      if (elem->_right != nullptr)
        q.push(elem->_right);
      // count减为0表示一层遍历结束
      // 此时队列中结点个数为下一层结点总数
      if (--count == 0) {
        count = q.size();
        height++;
      }
    }
  }
  return height;
}

template <typename T>
inline void IBinaryTree<T>::traverse(TraverseOrder order,
                                     TraverseFunc func) const {
  switch (order) {
  case TraverseOrder::In:
    inorder_recu(_root, func);
    break;
  case TraverseOrder::Pre:
    preorder_recu(_root, func);
    break;
  case TraverseOrder::Post:
    postorder_recu(_root, func);
    break;
  case TraverseOrder::Level:
    levelorder(_root, func);
    break;
  case TraverseOrder::Morris:
    morrisorder(_root, func);
    break;
  }
}

template <typename T>
inline void IBinaryTree<T>::inorder_recu(Node<T> *node,
                                         TraverseFunc func) const {
  if (node != nullptr) {
    inorder_recu(node->_left, func);
    if (func != nullptr)
      func(node->_data);
    else
      cout << *node->_data << "\n";
    inorder_recu(node->_right, func);
  }
}

template <typename T>
inline void IBinaryTree<T>::preorder_recu(Node<T> *node,
                                          TraverseFunc func) const {
  if (node != nullptr) {
    if (func != nullptr)
      func(node->_data);
    else
      cout << *node->_data << "\n";
    preorder_recu(node->_left, func);
    preorder_recu(node->_right, func);
  }
}

template <typename T>
inline void IBinaryTree<T>::postorder_recu(Node<T> *node,
                                           TraverseFunc func) const {
  if (node != nullptr) {
    postorder_recu(node->_left, func);
    postorder_recu(node->_right, func);
    if (func != nullptr)
      func(node->_data);
    else
      cout << *node->_data << "\n";
  }
}

template <typename T>
inline void IBinaryTree<T>::inorder_iter(TraverseFunc func) const {
  if (_root != nullptr) {
    Node<T> *node = _root;
    stack<Node<T> *> s;
    while (true) {
      if (node != nullptr) {
        s.push(node);
        node = node->_left;
      } else if (!s.empty()) {
        node = s.top();
        s.pop();
        if (func != nullptr)
          func(node->_data);
        else
          cout << *node->_data << "\n";
        node = node->_right;
      } else
        return;
    }
  }
}

template <typename T>
inline void IBinaryTree<T>::preorder_iter(TraverseFunc func) const {
  if (_root != nullptr) {
    stack<Node<T> *> s;
    s.push(_root);
    while (!s.empty()) {
      Node<T> *node = s.top();
      s.pop();
      if (func != nullptr)
        func(node->_data);
      else
        cout << *node->_data << "\n";
      if (node->_right != nullptr)
        s.push(node->_right);
      if (node->_left != nullptr)
        s.push(node->_left);
    }
  }
}

template <typename T>
inline void IBinaryTree<T>::postorder_iter(TraverseFunc func) const {
  if (_root != nullptr) {
    Node<T> *prev = nullptr;
    stack<Node<T> *> s;
    s.push(_root);
    while (!s.empty()) {
      Node<T> *top = s.top();
      if (top->is_leaf() || (prev != nullptr && prev->_parent == top)) {
        prev = s.pop();
        if (func != nullptr)
          func(prev->_data);
        else
          cout << *prev->_data << "\n";
      } else {
        if (top->_right != nullptr)
          s.push(top->_right);
        if (top->_left != nullptr)
          s.push(top->_left);
      }
    }
  }
}

template <typename T>
inline void IBinaryTree<T>::morrisorder(Node<T> *node,
                                        TraverseFunc func) const {
  while (node != nullptr) {
    if (node->_left != nullptr) {
      Node<T> *pred = node->_left;
      while (pred->_right != nullptr && pred->_right != node)
        pred = pred->_right;
      if (pred->_right == nullptr) {
        pred->_right = node; // 找到左结点最右侧的结点，将其后继置为根结点
        node = node->_left;
      } else {
        if (func != nullptr)
          func(pred->_right->_data);
        else
          cout << *pred->_right->_data << "\n";
        pred->_right = nullptr; // 该结点已指向后继，将其右指针置空
        node = node->_right;
      }
    } else {
      if (func != nullptr)
        func(node->_data);
      else
        cout << *node->_data << "\n";
      node = node->_right;
    }
  }
}

template <typename T>
inline void IBinaryTree<T>::levelorder(Node<T> *node, TraverseFunc func) const {
  if (node != nullptr) {
    queue<Node<T> *> q;
    q.push(node);
    while (!q.empty()) {
      Node<T> *elem = q.front();
      q.pop();
      if (elem->_left != nullptr)
        q.push(elem->_left);
      if (elem->_right != nullptr)
        q.push(elem->_right);
      if (func != nullptr)
        func(elem->_data);
      else
        cout << *elem->_data << "\n";
    }
  }
}
} // namespace app

#endif /* BINARY_TREE_HPP */