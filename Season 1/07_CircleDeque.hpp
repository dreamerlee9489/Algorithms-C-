#ifndef CIRCLE_DEQUE_HPP
#define CIRCLE_DEQUE_HPP

#include <iostream>
#include <memory>

using namespace std;

namespace app {
/**
 * @brief 循环双端队列
 * @date 2022-04-08
 * @tparam T
 */
template <typename T> class CircleDeque {
  template <typename U>
  friend ostream &operator<<(ostream &os, const CircleDeque<U> &deque);

  const size_t DEFAULT_CAPACITY = 8;
  size_t _capacity = 0, _size = 0, _front = 0;
  shared_ptr<T> *_array = nullptr;

  int true_index(int index) const;

  void ensure_capacity();

public:
  CircleDeque<T> &operator=(const CircleDeque<T> &deque);

  CircleDeque<T> &operator=(CircleDeque<T> &&deque) noexcept;

  CircleDeque();

  CircleDeque(const CircleDeque<T> &deque) { *this = deque; }

  CircleDeque(CircleDeque<T> &&deque) noexcept { *this = move(deque); }

  ~CircleDeque();

  size_t size() const { return _size; }

  size_t capacity() const { return _capacity; }

  bool is_empty() const { return _size == 0; }

  void push(shared_ptr<T> data);

  shared_ptr<T> pop();

  void push_front(shared_ptr<T> data);

  shared_ptr<T> pop_rear();

  shared_ptr<T> front() const { return _array[_front]; }

  shared_ptr<T> rear() const { return _array[true_index(_size - 1)]; }

  void clear();
};

template <typename U>
inline ostream &operator<<(ostream &os, const CircleDeque<U> &deque) {
  for (size_t i = 0; i < deque._capacity; ++i) {
    if (deque._array[i] != nullptr)
      os << *deque._array[i] << "\n";
    else
      os << "nullptr\n";
  }
  return os;
}

template <typename T>
inline CircleDeque<T> &CircleDeque<T>::operator=(const CircleDeque<T> &deque) {
  delete[] _array;
  _array = new shared_ptr<T>[deque._capacity];
  _capacity = deque._capacity;
  _size = deque._size;
  _front = deque._front;
  for (size_t i = 0; i < deque._capacity; ++i)
    _array[i] = deque._array[i];
  return *this;
}

template <typename T>
inline CircleDeque<T> &
CircleDeque<T>::operator=(CircleDeque<T> &&deque) noexcept {
  _array = deque._array;
  _capacity = deque._capacity;
  _size = deque._size;
  _front = deque._front;
  deque._size = 0;
  deque._front = 0;
  return *this;
}

template <typename T> inline CircleDeque<T>::CircleDeque() {
  _size = 0;
  _front = 0;
  _capacity = DEFAULT_CAPACITY;
  _array = new shared_ptr<T>[_capacity];
}

template <typename T> inline CircleDeque<T>::~CircleDeque() {
  clear();
  delete[] _array;
}

template <typename T> inline void CircleDeque<T>::push(shared_ptr<T> data) {
  ensure_capacity();
  _array[true_index(_size)] = data;
  _size++;
}

template <typename T> inline shared_ptr<T> CircleDeque<T>::pop() {
  shared_ptr<T> old = _array[_front];
  _array[_front] = nullptr;
  _front = true_index(1);
  _size--;
  return old;
}

template <typename T>
inline void CircleDeque<T>::push_front(shared_ptr<T> data) {
  ensure_capacity();
  _front = true_index(-1);
  _array[_front] = data;
  _size++;
}

template <typename T> inline shared_ptr<T> CircleDeque<T>::pop_rear() {
  int rear = true_index(_size - 1);
  shared_ptr<T> old = _array[rear];
  _array[rear] = nullptr;
  _size--;
  return old;
}

template <typename T> inline void CircleDeque<T>::clear() {
  for (size_t i = 0; i < _capacity; ++i)
    _array[i] = nullptr;
  _front = 0;
  _size = 0;
}

template <typename T> inline int CircleDeque<T>::true_index(int index) const {
  index += _front;
  if (index < 0)
    return index + _capacity;
  return index % _capacity;
}

template <typename T> inline void CircleDeque<T>::ensure_capacity() {
  if (_size >= _capacity) {
    shared_ptr<T> *old = _array;
    size_t new_cap = _capacity << 1;
    _array = new shared_ptr<T>[new_cap];
    for (size_t i = 0; i < _size; ++i)
      _array[i] = old[true_index(i)];
    _front = 0;
    _capacity = new_cap;
    delete[] old;
  }
}
} // namespace app

#endif /* CIRCLE_DEQUE_HPP */
