/**
 * @file 03_IList.h
 * @author dreamerlee9489@outlook.com
 * @brief 线性表基类(智能指针版)
 * @version 0.1
 * @date 2022-03-30
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ILIST_H
#define ILIST_H
#include <iostream>
#include <string>
#include <memory>

template <typename T>
class IList
{
protected:
    size_t _size = 0;
    void check_range(int index, bool isAdd = false) const;

public:
    IList() = default;
    virtual ~IList() = default;
    virtual int index_of(std::shared_ptr<T> data) const = 0;
    virtual void insert(int index, std::shared_ptr<T> data) = 0;
    virtual std::shared_ptr<T> remove(int index) = 0;
    virtual std::shared_ptr<T> get(int index) const = 0;
    virtual void set(int index, std::shared_ptr<T> data) = 0;
    virtual void clear() = 0;
    size_t size() const { return _size; }
    bool is_empty() const { return _size == 0; }
    bool contains(std::shared_ptr<T> data) const { return index_of(data) >= 0 ? true : false; }
    void add(std::shared_ptr<T> data) { return insert(_size, data); }
};

template <typename T>
inline void IList<T>::check_range(int index, bool isAdd) const
{
    if (!isAdd && (index >= _size || index < 0))
        throw std::out_of_range("index = " + std::to_string(index) + " out of range: [0, " + std::to_string(_size - 1) + "].");
    if (index > _size || index < 0)
        throw std::out_of_range("index = " + std::to_string(index) + " out of range for add: [0, " + std::to_string(_size) + "].");
}

#endif /* ILIST_H */
