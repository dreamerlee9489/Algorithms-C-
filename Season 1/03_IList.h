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
    void check_range(size_t index, bool isAdd = false);

public:
    IList() = default;
    virtual ~IList() = default;
    size_t size() { return _size; }
    bool is_empty() { return _size == 0; }
    bool contains(std::shared_ptr<T> element);
    void add(std::shared_ptr<T> element);
    virtual void insert(size_t index, std::shared_ptr<T> element) = 0;
    virtual size_t index_of(std::shared_ptr<T> element) = 0;
    virtual std::shared_ptr<T> remove(size_t index) = 0;
    virtual std::shared_ptr<T> get(size_t index) = 0;
    virtual void set(size_t index, std::shared_ptr<T> element) = 0;
    virtual void clear() = 0;
};

template <typename T>
void IList<T>::check_range(size_t index, bool isAdd)
{
    if (!isAdd && index >= _size)
        throw std::out_of_range("index = " + std::to_string(index) + " out of range: [0, " + std::to_string(_size - 1) + "].");
    if (index > _size)
        throw std::out_of_range("index = " + std::to_string(index) + " out of range for add: [0, " + std::to_string(_size) + "].");
}

template <typename T>
bool IList<T>::contains(std::shared_ptr<T> element)
{
    return index_of(element);
}

template <typename T>
void IList<T>::add(std::shared_ptr<T> element)
{
    insert(_size, element);
}

#endif
