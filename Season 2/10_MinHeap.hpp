#ifndef MIN_HPPEAP_HPP
#define MIN_HPPEAP_HPP
#include <cmath>
#include <queue>
#include <memory>
#include <iostream>
using namespace std;

namespace app
{
    /**
     * @brief 最小堆
     * @date 2022-05-09
     * @tparam T
     */
    template <typename T>
    class MinHeap
    {
        using Comparator = int (*)(T *a, T *b);
        using TraverseFunc = bool (*)(T *data);
        const size_t DEFAULT_CAPACITY = 8;
        size_t _size = 0;
        size_t _capacity = 0;
        T **_array = nullptr;
        Comparator _comparator = nullptr;
        void ensure_capacity();
        void sift_up(int index);
        void sift_down(int index);
        int compare(T *a, T *b)
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
        void heapify()
        {
            for (int i = (_size >> 1) - 1; i >= 0; --i)
                sift_down(i);
        }
        void heap_empty_check() const
        {
            if (_size == 0)
                throw out_of_range("heap is empty.");
        }
        void not_null_check(T *data) const
        {
            if (data == nullptr)
                throw invalid_argument("data must be not null.");
        }

    public:
        MinHeap<T> &operator=(const MinHeap<T> &heap);
        MinHeap<T> &operator=(MinHeap<T> &&heap) noexcept;
        MinHeap(T **array = nullptr, size_t size = 0, Comparator comparator = nullptr);
        MinHeap(const MinHeap<T> &heap) { *this = heap; }
        MinHeap(MinHeap<T> &&heap) noexcept { *this = move(heap); }
        ~MinHeap() { clear(); }
        size_t size() const { return _size; }
        size_t capacity() const { return _capacity; }
        bool is_empty() const { return _size == 0; }
        void add(T *data);
        T *remove();
        T *replace(T *data);
        T *get() const
        {
            heap_empty_check();
            return _array[0];
        }
        void clear()
        {
            for (size_t i = 0; i < _capacity; ++i)
                delete _array[i];
            _size = 0;
        }
        void traverse(TraverseFunc func = nullptr) const;
    };

    template <typename T>
    inline MinHeap<T> &MinHeap<T>::operator=(const MinHeap<T> &heap)
    {
        delete[] _array;
        _array = new T *[heap._capacity];
        _capacity = heap._capacity;
        _size = heap._size;
        _comparator = heap._comparator;
        for (size_t i = 0; i < heap._size; ++i)
            _array[i] = heap._array[i];
        return *this;
    }

    template <typename T>
    inline MinHeap<T> &MinHeap<T>::operator=(MinHeap<T> &&heap) noexcept
    {
        delete[] _array;
        _array = heap._array;
        _capacity = heap._capacity;
        _size = heap._size;
        _comparator = heap._comparator;
        heap._array = nullptr;
        heap._size = 0;
        return *this;
    }

    template <typename T>
    inline MinHeap<T>::MinHeap(T **array, size_t size, Comparator comparator)
    {
        _comparator = comparator;
        if (array == nullptr || size == 0)
        {
            _array = new T *[DEFAULT_CAPACITY];
            _capacity = DEFAULT_CAPACITY;
        }
        else
        {
            _size = size;
            _capacity = max(size, DEFAULT_CAPACITY);
            _array = new T *[_capacity];
            for (size_t i = 0; i < size; ++i)
                _array[i] = array[i];
            heapify();
        }
    }

    template <typename T>
    inline void MinHeap<T>::add(T *data)
    {
        not_null_check(data);
        ensure_capacity();
        _array[_size++] = data;
        sift_up(_size - 1);
    }

    template <typename T>
    inline T *MinHeap<T>::remove()
    {
        heap_empty_check();
        size_t last = --_size;
        T *root = _array[0];
        _array[0] = _array[last];
        _array[last] = nullptr;
        sift_down(0);
        return root;
    }

    template <typename T>
    inline T *MinHeap<T>::replace(T *data)
    {
        not_null_check(data);
        T *root = nullptr;
        if (_size == 0)
        {
            _array[0] = data;
            _size++;
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
    inline void MinHeap<T>::traverse(TraverseFunc func) const
    {
        if (_size > 0)
        {
            int index = 0, lv_cnt = 1;
            queue<T *> q;
            q.push(_array[index]);
            while (!q.empty())
            {
                size_t left = (index << 1) + 1, right = left + 1;
                lv_cnt--;
                index++;
                T *data = q.front();
                q.pop();
                if (left < _size)
                    q.push(_array[left]);
                if (right < _size)
                    q.push(_array[right]);
                if (func != nullptr)
                    func(data);
                else
                    cout << *data << "\t";
                if (lv_cnt == 0)
                {
                    lv_cnt = q.size();
                    cout << "\n";
                }
            }
        }
    }

    template <typename T>
    inline void MinHeap<T>::ensure_capacity()
    {
        if (_size >= _capacity)
        {
            T **old = _array;
            _capacity <<= 1;
            _array = new T *[_capacity];
            for (size_t i = 0; i < _size; ++i)
                _array[i] = old[i];
            delete[] old;
        }
    }

    template <typename T>
    inline void MinHeap<T>::sift_up(int index)
    {
        T *child = _array[index];
        while (index > 0)
        {
            int parent_index = (index - 1) >> 1;
            T *parent = _array[parent_index];
            if (compare(child, parent) > 0)
                break;
            _array[index] = parent;
            index = parent_index;
        }
        _array[index] = child;
    }

    template <typename T>
    inline void MinHeap<T>::sift_down(int index)
    {
        T *parent = _array[index];
        int half = _size >> 1;
        while (index < half)
        {
            int child_index = (index << 1) + 1, right_index = child_index + 1;
            T *child = _array[child_index];
            if (right_index < _size && compare(_array[child_index], _array[right_index]) >= 0)
                child = _array[child_index = right_index];
            if (compare(parent, child) < 0)
                break;
            _array[index] = child;
            index = child_index;
        }
        _array[index] = parent;
    }
} // namespace app

#endif /* MIN_HPPEAP_HPP */
