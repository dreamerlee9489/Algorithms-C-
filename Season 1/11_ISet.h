#ifndef ISET_H
#define ISET_H
#include <memory>
// 集合基类
template <typename T>
class ISet
{
protected:
    using traverse_func = bool (*)(std::shared_ptr<T> data);
    ISet() = default;
    ~ISet() = default;
    virtual size_t size() = 0;
    virtual bool is_empty() = 0;
    virtual bool contains(std::shared_ptr<T> data) = 0;
    virtual void add(std::shared_ptr<T> data) = 0;
    virtual void remove(std::shared_ptr<T> data) = 0;
    virtual void traverse(traverse_func func = nullptr) = 0;
    virtual void clear() = 0;
};

#endif /* ISET_H */
