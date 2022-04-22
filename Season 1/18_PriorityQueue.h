#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <memory>
#include "./17_BinaryHeap.h"
/**
 * @brief 优先级队列
 * @date 2022-04-22 
 * @tparam T 
 */
template <typename T>
class PriorityQueue
{
    using Comparator = int (*)(std::shared_ptr<T> a, std::shared_ptr<T> b);
    BinaryHeap<T> *heap = nullptr;

public:
    PriorityQueue(Comparator comparator = nullptr) { heap = new BinaryHeap<T>(comparator); }
    ~PriorityQueue() { delete heap; }
    size_t size() const { return heap->size(); }
    bool is_empty() const { return heap->is_empty(); }
    void clear() { heap->clear(); }
    void push(std::shared_ptr<T> data) { heap->add(data); }
    std::shared_ptr<T> pop() { return heap->remove(); }
    std::shared_ptr<T> front() const { return heap->get(); }
};

#endif /* PRIORITY_QUEUE_H */
