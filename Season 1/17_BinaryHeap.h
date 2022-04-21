#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H
#include "./17_IHeap.h"

template <typename T>
class BinaryHeap : public IHeap<T>
{
    using Comparator = int (*)(std::shared_ptr<T> a, std::shared_ptr<T> b);
    static constexpr size_t DEFAULT_CAPACITY = 8;
    std::shared_ptr<T> *_array = nullptr;
    Comparator _comparator = nullptr;
    size_t _size = 0, _capacity = DEFAULT_CAPACITY;
    void not_null_check(std::shared_ptr<T> data);
    void ensure_capacity();
    void sift_up(size_t index);

public:
    BinaryHeap(Comparator comparator = nullptr);
    ~BinaryHeap();
    size_t size() const override { return _size; }
    bool is_empty() const override { return _size == 0; }
    void add(std::shared_ptr<T> data);
    std::shared_ptr<T> get() const override { return nullptr; }
    std::shared_ptr<T> remove() override { return nullptr; }
    void clear();
};

template <typename T>
BinaryHeap<T>::BinaryHeap(Comparator comparator)
{
    _comparator = comparator;
    _array = new std::shared_ptr<T>[DEFAULT_CAPACITY];
}

template <typename T>
BinaryHeap<T>::~BinaryHeap()
{
    delete[] _array;
}

template <typename T>
void BinaryHeap<T>::clear()
{
    for(size_t i = 0; i < _capacity; ++i)
        _array[i] = nullptr;
    _size = 0;
}

template <typename T>
void BinaryHeap<T>::add(std::shared_ptr<T> data)
{
    not_null_check(data);
    ensure_capacity();
    _array[_size++] = data;
    sift_up(_size - 1);
}

template <typename T>
void BinaryHeap<T>::not_null_check(std::shared_ptr<T> data)
{
    if(data == nullptr)
        throw std::invalid_argument("data must be not null!");
}

template <typename T>
void BinaryHeap<T>::ensure_capacity()
{
    if (_size >= _capacity)
    {
        _capacity <<= 1;
        auto temp = new std::shared_ptr<T>[_capacity];
        for (size_t i = 0; i < _size; ++i)
            temp[i] = _array[i];
        _array = temp;
    }
}

template <typename T>
void BinaryHeap<T>::sift_up(size_t index)
{
}

#endif /* BINARY_HEAP_H */


