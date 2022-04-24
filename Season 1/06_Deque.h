#ifndef DEQUE_H
#define DEQUE_H
#include "./03_LinkedList.h"
/**
 * @brief 双端队列
 * @date 2022-04-08
 * @tparam T
 */
template <typename T>
class Deque
{
    friend STD_ ostream &operator<<(STD_ ostream &os, const Deque<T> &deque) { return os << *deque._list; }
    LinkedList<T> *_list = nullptr;

public:
    Deque<T> &operator=(const Deque<T> &deque);
    Deque<T> &operator=(Deque<T> &&deque) noexcept;
    Deque() { _list = new LinkedList<T>(); }
    Deque(const Deque<T> &deque) { *this = deque; }
    Deque(Deque<T> &&deque) noexcept { *this = STD_ move(deque); }
    ~Deque() { delete _list; }
    size_t size() const { return _list->size(); }
    bool is_empty() const { return _list->size() == 0; }
    void push(STD_ shared_ptr<T> data) { _list->add(data); }
    STD_ shared_ptr<T> pop() { return _list->remove(0); }
    void push_front(STD_ shared_ptr<T> data) { _list->insert(0, data); }
    STD_ shared_ptr<T> pop_rear() { return _list->remove(_list->size() - 1); }
    STD_ shared_ptr<T> front() const { return _list->get(0); }
    STD_ shared_ptr<T> rear() const { return _list->get(_list->size() - 1); }
    void clear() { _list->clear(); }
};

template <typename T>
inline Deque<T> &Deque<T>::operator=(const Deque<T> &deque)
{
    clear();
    delete _list;
    _list = new LinkedList<T>();
    *_list = *deque._list;
    return *this;
}

template <typename T>
inline Deque<T> &Deque<T>::operator=(Deque<T> &&deque) noexcept
{
    clear();
    delete _list;
    _list = new LinkedList<T>();
    *_list = STD_ move(*deque._list);
    return *this;
}

#endif /* DEQUE_H */
