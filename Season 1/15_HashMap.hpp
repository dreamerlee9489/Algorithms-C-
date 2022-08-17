#ifndef HASH_MAP_HPP
#define HASH_MAP_HPP

#include "./14_IMap.hpp"

namespace app {
/**
 * @brief 哈希映射
 * @date 2022-04-20
 * @tparam K
 * @tparam V
 */
template <typename K, typename V> class HashMap : public IMap<K, V> {
protected:
  static const bool BLACK = false, RED = true;
  static const size_t DEFAULT_CAPACITY = 16;
  static constexpr double LOAD_FACTOR = 0.75;

  template <typename _K, typename _V> struct Node {
    friend ostream &operator<<(ostream &os, const Node &node) {
      return os << "<" << *node._key << "-" << *node._value << ">";
    }

    size_t _hash = 0;
    bool _color = RED;
    shared_ptr<_K> _key = nullptr;
    shared_ptr<_V> _value = nullptr;
    Node<_K, _V> *_parent = nullptr, *_left = nullptr, *_right = nullptr;

    Node<_K, _V> &operator=(const Node<_K, _V> &node);

    Node<_K, _V> &operator=(Node<_K, _V> &&node) noexcept;

    Node(shared_ptr<_K> key, shared_ptr<_V> value,
         Node<_K, _V> *parent = nullptr, Node<_K, _V> *left = nullptr,
         Node<_K, _V> *right = nullptr)
        : _key(key), _value(value), _parent(parent), _left(left),
          _right(right) {
      _hash = _key == nullptr ? 0 : hash<_K>()(*key);
    }

    Node(const Node<_K, _V> &node) { *this = node; }

    Node(Node<_K, _V> &&node) noexcept { *this = move(node); }

    virtual ~Node() {
      _key = nullptr;
      _value = nullptr;
    }

    bool is_leaf() const { return _left == nullptr && _right == nullptr; }

    bool is_binary() const { return _left != nullptr && _right != nullptr; }

    bool is_left() const {
      return _parent != nullptr && this == _parent->_left;
    }

    bool is_right() const {
      return _parent != nullptr && this == _parent->_right;
    }

    Node<_K, _V> *get_sibling() const;
  };

  size_t _size = 0, _capacity = DEFAULT_CAPACITY;
  Node<K, V> **_table = nullptr;
  typename IMap<K, V>::Comparator _comparator = nullptr;

  Node<K, V> *get_node(shared_ptr<K> key) const {
    Node<K, V> *root = _table[get_index(key)];
    return root == nullptr ? nullptr : get_node(root, key);
  }

  Node<K, V> *get_node(Node<K, V> *node, shared_ptr<K> key1) const;

  Node<K, V> *get_successor(Node<K, V> *node) const;

  /**
   * @brief 获取哈希表索引
   * @remark 哈希值与数组长度取模可以生成索引值
   *         为了提升效率, 使用位与代替取模(哈希表长度必为2^n)
   * @param node
   * @return int
   */
  int get_index(Node<K, V> *node) const {
    return node->_hash & (_capacity - 1);
  }

  int get_index(shared_ptr<K> key) const {
    return get_hash(key) & (_capacity - 1);
  }

  size_t get_hash(shared_ptr<K> key) const {
    if (key != nullptr)
      return hash<K>()(*key);
    return 0;
  }

  /**
   * @brief 元素数量 / 哈希表长度 > 装填因子时扩容
   */
  void ensure_capacity();

  void move_node(Node<K, V> *newnode);

  void after_add(Node<K, V> *node);

  void after_remove(Node<K, V> *node);

  void rotate_left(Node<K, V> *grand);

  void rotate_right(Node<K, V> *grand);

  void after_rotate(Node<K, V> *grand, Node<K, V> *parent, Node<K, V> *child);

  Node<K, V> *set_color(Node<K, V> *node, bool color);

  bool color_of(Node<K, V> *node) const {
    return node == nullptr ? BLACK : node->_color;
  }

  bool is_black(Node<K, V> *node) const { return color_of(node) == BLACK; }

  bool is_red(Node<K, V> *node) const { return color_of(node) == RED; }

  void clear_recu(Node<K, V> *root);

  virtual Node<K, V> *create_node(shared_ptr<K> key, shared_ptr<V> value,
                                  Node<K, V> *parent) {
    return new Node<K, V>(key, value, parent);
  }

  virtual void after_remove_derived(Node<K, V> *willnode, Node<K, V> *rmvnode) {
    delete rmvnode;
  }

public:
  HashMap<K, V> &operator=(const HashMap<K, V> &map);

  HashMap<K, V> &operator=(HashMap<K, V> &&map) noexcept;

  HashMap(typename IMap<K, V>::Comparator comparator = nullptr) {
    _comparator = comparator;
    _table = new Node<K, V> *[DEFAULT_CAPACITY];
    for (size_t i = 0; i < _capacity; ++i)
      _table[i] = nullptr;
  }

  virtual ~HashMap() {
    clear();
    delete[] _table;
  }

  HashMap(const HashMap<K, V> &map) { *this = map; }

  HashMap(HashMap<K, V> &&map) noexcept { *this = move(map); }

  size_t size() const override { return _size; }

  size_t capacity() const { return _capacity; }

  bool is_empty() const override { return _size == 0; }

  bool contains_key(shared_ptr<K> key) const override {
    return get_node(key) != nullptr;
  }

  bool contains_value(shared_ptr<V> value) const override;

  shared_ptr<V> get_value(shared_ptr<K> key) const override {
    Node<K, V> *node = get_node(key);
    return node != nullptr ? node->_value : nullptr;
  }

  shared_ptr<V> add(shared_ptr<K> key, shared_ptr<V> value) override;

  shared_ptr<V> remove(shared_ptr<K> key) override;

  virtual void traverse(typename IMap<K, V>::TraverseFunc func = nullptr) const;

  void clear() override {
    if (_size > 0) {
      _size = 0;
      for (size_t i = 0; i < _capacity; ++i)
        clear_recu(_table[i]);
    }
  }
};

template <typename K, typename V>
template <typename _K, typename _V>
inline typename HashMap<K, V>::template Node<_K, _V> &
HashMap<K, V>::Node<_K, _V>::operator=(const Node<_K, _V> &node) {
  _key = node._key;
  _value = node._value;
  _parent = node._parent;
  _left = node._left;
  _right = node._right;
  _color = node._color;
  _hash = node._hash;
  return *this;
}

template <typename K, typename V>
template <typename _K, typename _V>
inline typename HashMap<K, V>::template Node<_K, _V> &
HashMap<K, V>::Node<_K, _V>::operator=(Node<_K, _V> &&node) noexcept {
  _key = nullptr;
  _value = nullptr;
  this = &node;
  return *this;
}

template <typename K, typename V>
template <typename _K, typename _V>
inline typename HashMap<K, V>::template Node<_K, _V> *
HashMap<K, V>::Node<_K, _V>::get_sibling() const {
  if (is_left())
    return _parent->_right;
  else if (is_right())
    return _parent->_left;
  return nullptr;
}

template <typename K, typename V>
inline HashMap<K, V> &HashMap<K, V>::operator=(const HashMap<K, V> &map) {
  clear();
  delete[] _table;
  _capacity = DEFAULT_CAPACITY;
  _table = new Node<K, V> *[_capacity];
  _comparator = map._comparator;
  for (size_t i = 0; i < _capacity; ++i)
    _table[i] = nullptr;
  if (map._size > 0) {
    queue<Node<K, V> *> q;
    for (size_t i = 0; i < map._capacity; ++i) {
      if (map._table[i] != nullptr) {
        q.push(map._table[i]);
        while (!q.empty()) {
          Node<K, V> *node = q.front();
          add(node->_key, node->_value);
          q.pop();
          if (node->_left != nullptr)
            q.push(node->_left);
          if (node->_right != nullptr)
            q.push(node->_right);
        }
      }
    }
  }
  return *this;
}

template <typename K, typename V>
inline HashMap<K, V> &HashMap<K, V>::operator=(HashMap<K, V> &&map) noexcept {
  clear();
  _size = map._size;
  _capacity = map._capacity;
  _comparator = map._comparator;
  _table = map._table;
  map._size = 0;
  map._comparator = nullptr;
  map._table = nullptr;
  return *this;
}

template <typename K, typename V>
inline bool HashMap<K, V>::contains_value(shared_ptr<V> value) const {
  if (_size != 0) {
    queue<Node<K, V> *> q;
    for (size_t i = 0; i < _capacity; ++i) {
      if (_table[i] != nullptr) {
        q.push(_table[i]);
        while (!q.empty()) {
          Node<K, V> *node = q.front();
          q.pop();
          if (*value == *node->_value)
            return true;
          if (node->_left != nullptr)
            q.push(node->_left);
          if (node->_right != nullptr)
            q.push(node->_right);
        }
      }
    }
  }
  return false;
}

template <typename K, typename V>
inline shared_ptr<V> HashMap<K, V>::add(shared_ptr<K> key,
                                        shared_ptr<V> value) {
  ensure_capacity();
  int index = get_index(key);
  Node<K, V> *root = _table[index];
  if (root == nullptr) {
    root = this->create_node(key, value, nullptr);
    _table[index] = root;
    _size++;
    after_add(root);
    return nullptr;
  }
  Node<K, V> *parent = root, *node = root;
  int cmp = 0;
  shared_ptr<K> key1 = key;
  size_t hash1 = get_hash(key1);
  Node<K, V> *result = nullptr;
  bool scanned = false;
  while (node != nullptr) {
    parent = node;
    shared_ptr<K> key2 = node->_key;
    size_t hash2 = node->_hash;
    if (hash1 > hash2)
      cmp = 1;
    else if (hash1 < hash2)
      cmp = -1;
    else if (*key1 == *key2)
      cmp = 0;
    else if (key1 != nullptr && key2 != nullptr && _comparator != nullptr &&
             typeid(*key1) == typeid(*key2) &&
             (cmp = _comparator(key1, key2)) != 0) {
    } else if (scanned)
      cmp = key1.get() - key2.get();
    else {
      if (node->_left != nullptr &&
              (result = get_node(node->_left, key1)) != nullptr ||
          (node->_right != nullptr &&
           (result = get_node(node->_right, key1)) != nullptr)) {
        node = result;
        cmp = 0;
      } else {
        scanned = true;
        cmp = key1.get() - key2.get();
      }
    }
    if (cmp > 0)
      node = node->_right;
    else if (cmp < 0)
      node = node->_left;
    else {
      shared_ptr<V> old = node->_value;
      node->_key = key;
      node->_value = value;
      node->_hash = hash1;
      return old;
    }
  }
  Node<K, V> *newnode = this->create_node(key, value, parent);
  if (cmp > 0)
    parent->_right = newnode;
  else
    parent->_left = newnode;
  _size++;
  after_add(newnode);
  return nullptr;
}

template <typename K, typename V>
inline shared_ptr<V> HashMap<K, V>::remove(shared_ptr<K> key) {
  Node<K, V> *node = get_node(key);
  if (node != nullptr) {
    _size--;
    Node<K, V> *willnode = node;
    shared_ptr<V> old = node->_value;
    if (node->is_binary()) {
      Node<K, V> *s = get_successor(node);
      node->_key = s->_key;
      node->_value = s->_value;
      node->_hash = s->_hash;
      node = s;
    }
    Node<K, V> *replace = node->_left != nullptr ? node->_left : node->_right;
    int index = get_index(node);
    if (replace != nullptr) {
      replace->_parent = node->_parent;
      if (node->_parent == nullptr)
        _table[index] = replace;
      else if (node == node->_parent->_left)
        node->_parent->_left = replace;
      else
        node->_parent->_right = replace;
      after_remove(replace);
    } else if (node->_parent != nullptr) {
      if (node == node->_parent->_left)
        node->_parent->_left = nullptr;
      else
        node->_parent->_right = nullptr;
      after_remove(node);
    } else {
      _table[index] = nullptr;
    }
    this->after_remove_derived(willnode, node);
    return old;
  }
  return nullptr;
}

template <typename K, typename V>
inline void
HashMap<K, V>::traverse(typename IMap<K, V>::TraverseFunc func) const {
  if (_size > 0) {
    queue<Node<K, V> *> q;
    for (size_t i = 0; i < _capacity; ++i) {
      if (_table[i] != nullptr) {
        cout << "---------- " << i << " ----------\n";
        q.push(_table[i]);
        size_t lv_cnt = 1;
        while (!q.empty()) {
          Node<K, V> *node = q.front();
          q.pop();
          lv_cnt--;
          if (node->_left != nullptr)
            q.push(node->_left);
          if (node->_right != nullptr)
            q.push(node->_right);
          if (func != nullptr)
            func(node->_key, node->_value);
          else
            cout << *node << "\t";
          if (lv_cnt == 0) {
            lv_cnt = q.size();
            cout << "\n";
          }
        }
      }
    }
  }
}

template <typename K, typename V>
inline typename HashMap<K, V>::template Node<K, V> *
HashMap<K, V>::get_node(Node<K, V> *node, shared_ptr<K> key1) const {
  size_t hash1 = get_hash(key1);
  Node<K, V> *result = nullptr;
  int cmp = 0;
  while (node != nullptr) {
    shared_ptr<K> key2 = node->_key;
    size_t hash2 = node->_hash;
    if (hash1 > hash2)
      node = node->_right;
    else if (hash1 < hash2)
      node = node->_left;
    else if (*key1 == *key2)
      return node;
    else if (key1 != nullptr && key2 != nullptr && _comparator != nullptr &&
             typeid(*key1) == typeid(*key2) &&
             (cmp = _comparator(key1, key2)) != 0)
      node = cmp > 0 ? node->_right : node->_left;
    else if (node->_right != nullptr &&
             (result = get_node(node->_right, key1)) != nullptr)
      return result;
    else
      node = node->_left;
  }
  return nullptr;
}

template <typename K, typename V>
inline typename HashMap<K, V>::template Node<K, V> *
HashMap<K, V>::get_successor(Node<K, V> *node) const {
  if (node != nullptr) {
    Node<K, V> *p = node->_right;
    if (p != nullptr) {
      while (p->_left != nullptr)
        p = p->_left;
      return p;
    }
    while (node->_parent != nullptr && node == node->_parent->_right)
      node = node->_parent;
    return node->_parent;
  }
  return nullptr;
}

template <typename K, typename V> inline void HashMap<K, V>::ensure_capacity() {
  if (_size * 1.0 / _capacity * 1.0 > LOAD_FACTOR) {
    Node<K, V> **old = _table;
    _table = new Node<K, V> *[_capacity << 1];
    for (size_t i = 0; i < _capacity << 1; ++i)
      _table[i] = nullptr;
    queue<Node<K, V> *> q;
    for (size_t i = 0; i < _capacity; ++i) {
      if (old[i] != nullptr) {
        q.push(old[i]);
        while (!q.empty()) {
          Node<K, V> *node = q.front();
          q.pop();
          if (node->_left != nullptr)
            q.push(node->_left);
          if (node->_right != nullptr)
            q.push(node->_right);
          move_node(node);
        }
      }
    }
    _capacity <<= 1;
    delete[] old;
  }
}

template <typename K, typename V>
inline void HashMap<K, V>::move_node(Node<K, V> *newnode) {
  newnode->_parent = nullptr;
  newnode->_left = nullptr;
  newnode->_right = nullptr;
  newnode->_color = RED;
  int index = get_index(newnode);
  Node<K, V> *root = _table[index];
  if (root == nullptr) {
    root = newnode;
    _table[index] = root;
    after_add(root);
    return;
  }
  Node<K, V> *parent = root, *node = root;
  int cmp = 0;
  shared_ptr<K> key1 = newnode->_key;
  size_t hash1 = newnode->_hash;
  while (node != nullptr) {
    parent = node;
    shared_ptr<K> key2 = node->_key;
    size_t hash2 = node->_hash;
    if (hash1 > hash2)
      cmp = 1;
    else if (hash1 < hash2)
      cmp = -1;
    else if (key1 != nullptr && key2 != nullptr && _comparator != nullptr &&
             typeid(*key1) == typeid(*key2) &&
             (cmp = _comparator(key1, key2)) != 0) {
    } else
      cmp = key1.get() - key2.get();

    if (cmp > 0)
      node = node->_right;
    else if (cmp < 0)
      node = node->_left;
  }
  newnode->_parent = parent;
  if (cmp > 0)
    parent->_right = newnode;
  else
    parent->_left = newnode;
  after_add(newnode);
}

template <typename K, typename V>
inline void HashMap<K, V>::after_add(Node<K, V> *node) {
  Node<K, V> *parent = node->_parent;
  if (parent == nullptr) {
    set_color(node, BLACK);
    return;
  }
  if (is_red(parent)) {
    Node<K, V> *uncle = parent->get_sibling();
    Node<K, V> *grand = set_color(parent->_parent, RED);
    if (is_red(uncle)) {
      set_color(parent, BLACK);
      set_color(uncle, BLACK);
      after_add(grand);
      return;
    }
    if (parent->is_left()) {
      if (node->is_left())
        set_color(parent, BLACK);
      else {
        set_color(node, BLACK);
        rotate_left(parent);
      }
      rotate_right(grand);
    } else {
      if (node->is_left()) {
        set_color(node, BLACK);
        rotate_right(parent);
      } else
        set_color(parent, BLACK);
      rotate_left(grand);
    }
  }
}

template <typename K, typename V>
inline void HashMap<K, V>::after_remove(Node<K, V> *node) {
  if (is_red(node)) {
    set_color(node, BLACK);
    return;
  }
  Node<K, V> *parent = node->_parent;
  if (parent != nullptr) {
    bool is_left = parent->_left == nullptr || node->is_left();
    Node<K, V> *sibling = is_left ? parent->_right : parent->_left;
    if (is_left) {
      if (is_red(sibling)) {
        set_color(sibling, BLACK);
        set_color(parent, RED);
        rotate_left(parent);
        sibling = parent->_right;
      }
      if (is_black(sibling->_left) && is_black(sibling->_right)) {
        bool parent_black = is_black(parent);
        set_color(parent, BLACK);
        set_color(sibling, RED);
        if (parent_black)
          after_remove(parent);
      } else {
        if (is_black(sibling->_right)) {
          rotate_right(sibling);
          sibling = parent->_right;
        }
        set_color(sibling, color_of(parent));
        set_color(sibling->_right, BLACK);
        set_color(parent, BLACK);
        rotate_left(parent);
      }
    } else {
      if (is_red(sibling)) {
        set_color(sibling, BLACK);
        set_color(parent, RED);
        rotate_right(parent);
        sibling = parent->_left;
      }
      if (is_black(sibling->_left) && is_black(sibling->_right)) {
        bool parent_black = is_black(parent);
        set_color(parent, BLACK);
        set_color(sibling, RED);
        if (parent_black)
          after_remove(parent);
      } else {
        if (is_black(sibling->_left)) {
          rotate_left(sibling);
          sibling = parent->_left;
        }
        set_color(sibling, color_of(parent));
        set_color(sibling->_left, BLACK);
        set_color(parent, BLACK);
        rotate_right(parent);
      }
    }
  }
}

template <typename K, typename V>
inline void HashMap<K, V>::rotate_left(Node<K, V> *grand) {
  Node<K, V> *parent = grand->_right;
  Node<K, V> *child = parent->_left;
  grand->_right = child;
  parent->_left = grand;
  after_rotate(grand, parent, child);
}

template <typename K, typename V>
inline void HashMap<K, V>::rotate_right(Node<K, V> *grand) {
  Node<K, V> *parent = grand->_left;
  Node<K, V> *child = parent->_right;
  grand->_left = child;
  parent->_right = grand;
  after_rotate(grand, parent, child);
}

template <typename K, typename V>
inline void HashMap<K, V>::after_rotate(Node<K, V> *grand, Node<K, V> *parent,
                                        Node<K, V> *child) {
  parent->_parent = grand->_parent;
  if (grand->is_left())
    grand->_parent->_left = parent;
  else if (grand->is_right())
    grand->_parent->_right = parent;
  else
    _table[get_index(grand)] = parent;
  if (child != nullptr)
    child->_parent = grand;
  grand->_parent = parent;
}

template <typename K, typename V>
inline typename HashMap<K, V>::template Node<K, V> *
HashMap<K, V>::set_color(Node<K, V> *node, bool color) {
  if (node != nullptr)
    node->_color = color;
  return node;
}

template <typename K, typename V>
inline void HashMap<K, V>::clear_recu(Node<K, V> *root) {
  if (root != nullptr) {
    clear_recu(root->_left);
    clear_recu(root->_right);
    delete root;
  }
}
} // namespace app

#endif /* HASH_MAP_HPP */