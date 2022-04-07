#ifndef DEQUE_H
#define DEQUE_H
#include "./03_LinkedList.h"

template <typename T>
class Deque
{
    friend std::ostream &operator<<(std::ostream &os, const Deque<T> &deque) { return os << *deque._list; }

private:
    LinkedList<T> *_list;

public:
    Deque() { _list = new LinkedList<T>(); }
    ~Deque() { delete _list; }
    size_t size() { return _list->size(); }
    bool is_empty() { return _list->size() == 0; }
    std::shared_ptr<T> en_queue(std::shared_ptr<T> data) { return _list->add(data); }
    std::shared_ptr<T> de_queue() { return _list->remove(0); }
    std::shared_ptr<T> en_queue_front(std::shared_ptr<T> data) { return _list->insert(0, data); }
    std::shared_ptr<T> de_queue_rear() { return _list->remove(_list->size() - 1); }
    std::shared_ptr<T> front() { return _list->get(0); }
    std::shared_ptr<T> rear() { return _list->get(_list->size() - 1); }
    void clear() { _list->clear(); }
};

#endif /* DEQUE_H */
