#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "./03_LinkedList.hpp"

namespace app {
    /**
     * @brief 队列
     * @date 2022-04-05
     * @tparam T
     */
    template<typename T>
    class Queue {
        friend ostream &operator<<(ostream &os, const Queue<T> &queue) { return os << *queue.pList; }

        LinkedList<T> *pList = nullptr;

    public:
        Queue<T> operator=(const Queue<T> &queue);

        Queue<T> operator=(Queue<T> &&queue) noexcept;

        Queue() { pList = new LinkedList<T>(); }

        Queue(const Queue<T> &queue) { *this = queue; }

        Queue(Queue<T> &&queue) noexcept { *this = move(queue); }

        ~Queue() { delete pList; }

        size_t size() const { return pList->size(); }

        bool is_empty() const { return pList->is_empty(); }

        void push(shared_ptr<T> data) { pList->add(data); }

        shared_ptr<T> pop() { return pList->remove(0); }

        shared_ptr<T> const front() { return pList->get(0); }

        void clear() { pList->clear(); }
    };

    template<typename T>
    inline Queue<T> Queue<T>::operator=(const Queue<T> &queue) {
        clear();
        delete pList;
        pList = new LinkedList<T>();
        *pList = *queue.pList;
        return *this;
    }

    template<typename T>
    inline Queue<T> Queue<T>::operator=(Queue<T> &&queue) noexcept {
        clear();
        delete pList;
        pList = new LinkedList<T>();
        *pList = move(*queue.pList);
        return *this;
    }
} // namespace app

#endif /* QUEUE_HPP */
