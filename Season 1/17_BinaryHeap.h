#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H
#include "./17_IHeap.h"
/**
 * @brief 二叉堆
 * @date 2022-04-22
 * @tparam T
 */
template <typename T>
class BinaryHeap : public IHeap<T>
{
    const size_t DEFAULT_CAPACITY = 8;
    size_t _capacity = DEFAULT_CAPACITY;
    std::shared_ptr<T> *_array = nullptr;
    void heap_empty_check() const;
    void not_null_check(std::shared_ptr<T> data) const;
    void ensure_capacity();
    void sift_up(int index);
    void sift_down(int index);
    void heapify();

public:
    BinaryHeap(typename IHeap<T>::Comparator comparator = nullptr, std::shared_ptr<T> *array = nullptr, size_t size = 0);
    ~BinaryHeap() { delete[] _array; }
    size_t capacity() const { return _capacity; }
    void add(std::shared_ptr<T> data) override;
    std::shared_ptr<T> get() const override;
    std::shared_ptr<T> remove() override;
    std::shared_ptr<T> replace(std::shared_ptr<T> data) override;
    void clear() override;
    void traverse(typename IHeap<T>::TraverseFunc func = nullptr) const override;
};

template <typename T>
inline BinaryHeap<T>::BinaryHeap(typename IHeap<T>::Comparator comparator, std::shared_ptr<T> *array, size_t size) : IHeap<T>(comparator)
{
    if (array == nullptr || size == 0)
        _array = new std::shared_ptr<T>[DEFAULT_CAPACITY];
    else
    {
        this->_size = size;
        _capacity = std::max(size, DEFAULT_CAPACITY);
        _array = new std::shared_ptr<T>[_capacity];
        for (size_t i = 0; i < size; ++i)
            _array[i] = array[i];
        heapify();
    }
}

template <typename T>
inline void BinaryHeap<T>::add(std::shared_ptr<T> data)
{
    not_null_check(data);
    ensure_capacity();
    _array[this->_size++] = data;
    sift_up(this->_size - 1);
}

template <typename T>
inline std::shared_ptr<T> BinaryHeap<T>::get() const
{
    heap_empty_check();
    return _array[0];
}

template <typename T>
inline std::shared_ptr<T> BinaryHeap<T>::remove()
{
    heap_empty_check();
    size_t last = --this->_size;
    std::shared_ptr<T> root = _array[0];
    _array[0] = _array[last];
    _array[last] = nullptr;
    sift_down(0);
    return root;
}

template <typename T>
inline std::shared_ptr<T> BinaryHeap<T>::replace(std::shared_ptr<T> data)
{
    not_null_check(data);
    std::shared_ptr<T> root = nullptr;
    if (this->_size == 0)
    {
        _array[0] = data;
        this->_size++;
    }
    else
    {
        root = _array[0];
        _array[0] = data;
        sift_down(0);
    }
    return root;
}

template <typename T>
inline void BinaryHeap<T>::clear()
{
    for (size_t i = 0; i < _capacity; ++i)
        _array[i] = nullptr;
    this->_size = 0;
}

template <typename T>
inline void BinaryHeap<T>::traverse(typename IHeap<T>::TraverseFunc func) const
{
    if (this->_size > 0)
    {
        int index = 0, lv_cnt = 1;
        std::queue<std::shared_ptr<T>> q;
        q.push(_array[index]);
        while (!q.empty())
        {
            size_t left = (index << 1) + 1, right = left + 1;
            lv_cnt--;
            index++;
            std::shared_ptr<T> data = q.front();
            q.pop();
            if (left < this->_size)
                q.push(_array[left]);
            if (right < this->_size)
                q.push(_array[right]);
            if (func != nullptr)
                func(data);
            else
                std::cout << *data << "\t";
            if (lv_cnt == 0)
            {
                lv_cnt = q.size();
                std::cout << "\n";
            }
        }
    }
}

template <typename T>
inline void BinaryHeap<T>::heap_empty_check() const
{
    if (this->_size == 0)
        throw std::out_of_range("heap is empty.");
}

template <typename T>
inline void BinaryHeap<T>::not_null_check(std::shared_ptr<T> data) const
{
    if (data == nullptr)
        throw std::invalid_argument("data must be not null.");
}

template <typename T>
inline void BinaryHeap<T>::ensure_capacity()
{
    if (this->_size >= _capacity)
    {
        std::shared_ptr<T> *old = _array;
        _capacity <<= 1;
        _array = new std::shared_ptr<T>[_capacity];
        for (size_t i = 0; i < this->_size; ++i)
            _array[i] = old[i];
        delete[] old;
    }
}

template <typename T>
inline void BinaryHeap<T>::sift_up(int index)
{
    std::shared_ptr<T> child = _array[index];
    while (index > 0)
    {
        int parent_index = (index - 1) >> 1;
        std::shared_ptr<T> parent = _array[parent_index];
        if (this->compare(child, parent) <= 0)
            break;
        _array[index] = parent;
        index = parent_index;
    }
    _array[index] = child;
}

template <typename T>
inline void BinaryHeap<T>::sift_down(int index)
{
    std::shared_ptr<T> parent = _array[index];
    int half = this->_size >> 1;
    while (index < half)
    {
        int child_index = (index << 1) + 1, right_index = child_index + 1;
        std::shared_ptr<T> child = _array[child_index];
        if (right_index < this->_size && this->compare(_array[child_index], _array[right_index]) < 0)
            child = _array[child_index = right_index];
        if (this->compare(parent, child) >= 0)
            break;
        _array[index] = child;
        index = child_index;
    }
    _array[index] = parent;
}

template <typename T>
inline void BinaryHeap<T>::heapify()
{
    for (int i = (this->_size >> 1) - 1; i >= 0; --i)
        sift_down(i);
}

#endif /* BINARY_HEAP_H */
