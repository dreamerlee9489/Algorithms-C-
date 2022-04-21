#ifndef IHEAP_H
#define IHEAP_H
#include <memory>
/**
 * @brief 堆基类
 * @date 2022-04-21
 * @tparam T 
 */
template <typename T>
class IHeap
{
protected:
    IHeap() = default;
    virtual ~IHeap() = default;
    virtual size_t size() const = 0;
    virtual bool is_empty() const = 0;
    virtual void add(std::shared_ptr<T> data) = 0;
    virtual std::shared_ptr<T> get() const = 0;
    virtual std::shared_ptr<T> remove() = 0;
    virtual void clear() = 0;
};

#endif /* IHEAP_H */
