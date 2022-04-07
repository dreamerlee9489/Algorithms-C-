#ifndef QUEUE_H
#define QUEUE_H
#include "./03_LinkedList.h"

template <typename T>
class Queue
{
    friend std::ostream &operator<<(std::ostream &os, const Queue<T> &queue) { return os << *queue._list; }

private:
    LinkedList<T> *_list;

public:
    Queue() { _list = new LinkedList<T>(); }
    ~Queue() { delete _list; }
    size_t size() { return _list->size(); }
    bool is_empty() { return _list->is_empty(); }
    std::shared_ptr<T> en_queue(std::shared_ptr<T> data) { return _list->add(data); }
    std::shared_ptr<T> de_queue() { return _list->remove(0); }
    std::shared_ptr<T> front() { return _list->get(0); }
    void clear() { _list->clear(); }
};

#endif /* QUEUE_H */
