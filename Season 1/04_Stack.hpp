#ifndef STACK_HPP
#define STACK_HPP

#include "./02_ArrayList.hpp"

namespace app {
/**
 * @brief 栈
 * @date 2022-04-05
 * @tparam T
 */
template <typename T> class Stack {
  friend ostream &operator<<(ostream &os, const Stack<T> &stack) {
    return os << *stack._list;
  }

  ArrayList<T> *_list = nullptr;

public:
  Stack<T> &operator=(const Stack<T> &stack);

  Stack<T> &operator=(Stack<T> &&stack) noexcept;

  Stack() { _list = new ArrayList<T>(); }

  Stack(const Stack<T> &stack) { *this = stack; }

  Stack(Stack<T> &&stack) noexcept { *this = move(stack); }

  ~Stack() { delete _list; }

  size_t size() const { return _list->size(); }

  bool is_empty() const { return _list->is_empty(); }

  void push(shared_ptr<T> data) { _list->add(data); }

  shared_ptr<T> pop() { return _list->remove(_list->size() - 1); }

  shared_ptr<T> top() const { return _list->get(_list->size() - 1); }

  void clear() { _list->clear(); }
};

template <typename T>
inline Stack<T> &Stack<T>::operator=(const Stack<T> &stack) {
  clear();
  delete _list;
  _list = new ArrayList<T>();
  *_list = *stack._list;
  return *this;
}

template <typename T>
inline Stack<T> &Stack<T>::operator=(Stack<T> &&stack) noexcept {
  clear();
  delete _list;
  _list = new ArrayList<T>();
  *_list = move(*stack._list);
  return *this;
}
} // namespace app

#endif /* STACK_HPP */
