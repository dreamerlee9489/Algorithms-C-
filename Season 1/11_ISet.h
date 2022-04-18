/**
 * @file 11_ISet.h
 * @author dreamerlee9489@outlook.com
 * @brief 集合基类
 * @version 0.1
 * @date 2022-04-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ISET_H
#define ISET_H
#include <memory>

template <typename T>
class ISet
{
protected:
    using TraverseFunc = bool (*)(std::shared_ptr<T> data);
    using Comparator = int (*)(std::shared_ptr<T> a, std::shared_ptr<T> b);
    ISet() = default;
    ~ISet() = default;
    virtual size_t size() = 0;
    virtual bool is_empty() = 0;
    virtual bool contains(std::shared_ptr<T> data) = 0;
    virtual void add(std::shared_ptr<T> data) = 0;
    virtual void remove(std::shared_ptr<T> data) = 0;
    virtual void traverse(TraverseFunc func = nullptr) = 0;
    virtual void clear() = 0;
};

#endif /* ISET_H */
