#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "./17_BinaryHeap.hpp"

namespace app {
    /**
     * @brief 优先级队列
     * @date 2022-04-22
     * @tparam T
     */
    template<typename T>
    class PriorityQueue {
        using Comparator = int (*)(shared_ptr<T> a, shared_ptr<T> b);
        BinaryHeap<T> *mHeap = nullptr;

    public:
        PriorityQueue(Comparator comparator = nullptr) { mHeap = new BinaryHeap<T>(comparator); }

        ~PriorityQueue() { delete mHeap; }

        size_t size() const { return mHeap->size(); }

        bool is_empty() const { return mHeap->is_empty(); }

        void clear() { mHeap->clear(); }

        void push(shared_ptr<T> data) { mHeap->add(data); }

        shared_ptr<T> pop() { return mHeap->remove(); }

        shared_ptr<T> front() const { return mHeap->get(); }
    };
} // namespace app

#endif /* PRIORITY_QUEUE_HPP */
