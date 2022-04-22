#ifndef IHEAP_H
#define IHEAP_H
#include <cmath>
#include <queue>
#include <memory>
#include <iostream>
/**
 * @brief 堆基类
 * @date 2022-04-21
 * @tparam T
 */
template <typename T>
class IHeap
{
protected:
    using Comparator = int (*)(std::shared_ptr<T> a, std::shared_ptr<T> b);
    using TraverseFunc = bool (*)(std::shared_ptr<T> data);
    size_t _size = 0;
    Comparator _comparator = nullptr;
    int compare(std::shared_ptr<T> a, std::shared_ptr<T> b);

public:
    IHeap(Comparator comparator = nullptr) { _comparator = comparator; }
    virtual ~IHeap() = default;
    size_t size() const { return _size; }
    bool is_empty() const { return _size == 0; }
    virtual void add(std::shared_ptr<T> data) = 0;
    virtual std::shared_ptr<T> get() const = 0;
    virtual std::shared_ptr<T> remove() = 0;
    virtual std::shared_ptr<T> replace(std::shared_ptr<T> data) = 0;
    virtual void clear() = 0;
    virtual void traverse(TraverseFunc func = nullptr) = 0;
};

template <typename T>
int IHeap<T>::compare(std::shared_ptr<T> a, std::shared_ptr<T> b)
{
    if (_comparator != nullptr)
        return _comparator(a, b);
    else
    {
        if (*a < *b)
            return -1;
        else if (*a > *b)
            return 1;
        return 0;
    }
}

#endif /* IHEAP_H */
