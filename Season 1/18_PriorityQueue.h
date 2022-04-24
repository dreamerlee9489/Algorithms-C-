#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include "./17_BinaryHeap.h"
/**
 * @brief 优先级队列
 * @date 2022-04-22 
 * @tparam T 
 */
template <typename T>
class PriorityQueue
{
    using Comparator = int (*)(STD_ shared_ptr<T> a, STD_ shared_ptr<T> b);
    BinaryHeap<T> *heap = nullptr;

public:
    PriorityQueue(Comparator comparator = nullptr) { heap = new BinaryHeap<T>(comparator); }
    ~PriorityQueue() { delete heap; }
    size_t size() const { return heap->size(); }
    bool is_empty() const { return heap->is_empty(); }
    void clear() { heap->clear(); }
    void push(STD_ shared_ptr<T> data) { heap->add(data); }
    STD_ shared_ptr<T> pop() { return heap->remove(); }
    STD_ shared_ptr<T> front() const { return heap->get(); }
};

#endif /* PRIORITY_QUEUE_H */
