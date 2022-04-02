#ifndef ILIST_H
#define ILIST_H
#include <iostream>
#include <string>
#include <memory>
// 线性表基类(智能指针版)
template <typename T>
class IList
{
protected:
    size_t _size = 0;
    void check_range(int index, bool isAdd = false) const;

public:
    IList() = default;
    virtual ~IList() = default;
    size_t size() { return _size; }
    bool is_empty() { return _size == 0; }
    bool contains(std::shared_ptr<T> data) { return index_of(data); }
    std::shared_ptr<T> add(std::shared_ptr<T> data) { return insert(_size, data); }
    virtual int index_of(std::shared_ptr<T> data) = 0;
    virtual std::shared_ptr<T> insert(int index, std::shared_ptr<T> data) = 0;
    virtual std::shared_ptr<T> remove(int index) = 0;
    virtual std::shared_ptr<T> get(int index) const = 0;
    virtual std::shared_ptr<T> set(int index, std::shared_ptr<T> data) = 0;
    virtual void clear() = 0;
};

template <typename T>
void IList<T>::check_range(int index, bool isAdd) const
{
    if (!isAdd && (index >= _size || index < 0))
        throw std::out_of_range("index = " + std::to_string(index) + " out of range: [0, " + std::to_string(_size - 1) + "].");
    if (index > _size || index < 0)
        throw std::out_of_range("index = " + std::to_string(index) + " out of range for add: [0, " + std::to_string(_size) + "].");
}

#endif
