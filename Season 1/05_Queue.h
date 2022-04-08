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
    inline Queue<T> operator=(const Queue<T> &queue);
    inline Queue<T> operator=(Queue<T> &&queue) noexcept;
    Queue() { _list = new LinkedList<T>(); }
    ~Queue() { delete _list; }
    Queue(const Queue<T> &queue) { *this = queue; }
    Queue(Queue<T> &&queue) noexcept { *this = std::move(queue); }
    size_t size() const { return _list->size(); }
    bool is_empty() const { return _list->is_empty(); }
    std::shared_ptr<T> enqueue(std::shared_ptr<T> data) { return _list->add(data); }
    std::shared_ptr<T> dequeue() { return _list->remove(0); }
    std::shared_ptr<T> const front() { return _list->get(0); }
    void clear() { _list->clear(); }
};

template <typename T>
Queue<T> Queue<T>::operator=(const Queue<T> &queue)
{
    clear();
    delete _list;
    _list = new LinkedList<T>();
    *_list = *queue._list;
    return *this;
}

template <typename T>
Queue<T> Queue<T>::operator=(Queue<T> &&queue) noexcept
{
    clear();
    delete _list;
    _list = new LinkedList<T>();
    *_list = std::move(*queue._list);
    return *this;
}

#endif /* QUEUE_H */
