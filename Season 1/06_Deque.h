#ifndef DEQUE_H
#define DEQUE_H
#include "./03_LinkedList.h"
// 双端队列
template <typename T>
class Deque
{
    friend std::ostream &operator<<(std::ostream &os, const Deque<T> &deque) { return os << *deque._list; }

private:
    LinkedList<T> *_list;

public:
    Deque<T> &operator=(const Deque<T> &deque);
    Deque<T> &operator=(Deque<T> &&deque) noexcept;
    Deque() { _list = new LinkedList<T>(); }
    ~Deque() { delete _list; }
    Deque(const Deque<T> &deque) { *this = deque; }
    Deque(Deque<T> &&deque) noexcept { *this = std::move(deque); }
    size_t size() const { return _list->size(); }
    bool is_empty() const { return _list->size() == 0; }
    std::shared_ptr<T> push(std::shared_ptr<T> data) { return _list->add(data); }
    std::shared_ptr<T> pop() { return _list->remove(0); }
    std::shared_ptr<T> push_front(std::shared_ptr<T> data) { return _list->insert(0, data); }
    std::shared_ptr<T> pop_rear() { return _list->remove(_list->size() - 1); }
    std::shared_ptr<T> front() const { return _list->get(0); }
    std::shared_ptr<T> rear() const { return _list->get(_list->size() - 1); }
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
    *_list = std::move(*deque._list);
    return *this;
}

#endif /* DEQUE_H */
