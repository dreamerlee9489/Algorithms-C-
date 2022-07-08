#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "./03_LinkedList.hpp"

namespace app
{
    /**
     * @brief 队列
     * @date 2022-04-05
     * @tparam T
     */
    template <typename T>
    class Queue
    {
        friend ostream &operator<<(ostream &os, const Queue<T> &queue) { return os << *queue._list; }
        LinkedList<T> *_list = nullptr;

    public:
        Queue<T> operator=(const Queue<T> &queue);
        Queue<T> operator=(Queue<T> &&queue) noexcept;
        Queue() { _list = new LinkedList<T>(); }
        Queue(const Queue<T> &queue) { *this = queue; }
        Queue(Queue<T> &&queue) noexcept { *this = move(queue); }
        ~Queue() { delete _list; }
        size_t size() const { return _list->size(); }
        bool is_empty() const { return _list->is_empty(); }
        void push(shared_ptr<T> data) { _list->add(data); }
        shared_ptr<T> pop() { return _list->remove(0); }
        shared_ptr<T> const front() { return _list->get(0); }
        void clear() { _list->clear(); }
    };

    template <typename T>
    inline Queue<T> Queue<T>::operator=(const Queue<T> &queue)
    {
        clear();
        delete _list;
        _list = new LinkedList<T>();
        *_list = *queue._list;
        return *this;
    }

    template <typename T>
    inline Queue<T> Queue<T>::operator=(Queue<T> &&queue) noexcept
    {
        clear();
        delete _list;
        _list = new LinkedList<T>();
        *_list = move(*queue._list);
        return *this;
    }
} // namespace app

#endif /* QUEUE_HPP */
