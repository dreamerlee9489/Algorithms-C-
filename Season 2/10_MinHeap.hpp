#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <cmath>
#include <queue>
#include <memory>
#include <iostream>

using namespace std;

namespace app {
    /**
     * @brief 最小堆
     * @date 2022-05-09
     * @tparam T
     */
    template<typename T>
    class MinHeap {
        using Comparator = int (*)(T *a, T *b);
        using TraverseFunc = bool (*)(T *data);
        const size_t DEFAULT_CAPACITY = 8;
        size_t mSize = 0;
        size_t mCapacity = 0;
        T **pArray = nullptr;
        Comparator mComparator = nullptr;

        void ensuremCapacity();

        void sift_up(int index);

        void sift_down(int index);

        int compare(T *a, T *b) {
            if (mComparator != nullptr)
                return mComparator(a, b);
            else {
                if (*a < *b)
                    return -1;
                else if (*a > *b)
                    return 1;
                return 0;
            }
        }

        void heapify() {
            for (int i = (mSize >> 1) - 1; i >= 0; --i)
                sift_down(i);
        }

        void heap_empty_check() const {
            if (mSize == 0)
                throw out_of_range("heap is empty.");
        }

        void not_null_check(T *data) const {
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

        size_t size() const { return mSize; }

        size_t capacity() const { return mCapacity; }

        bool is_empty() const { return mSize == 0; }

        void add(T *data);

        T *remove();

        T *replace(T *data);

        T *get() const {
            heap_empty_check();
            return pArray[0];
        }

        void clear() {
            for (size_t i = 0; i < mCapacity; ++i)
                delete pArray[i];
            mSize = 0;
        }

        void traverse(TraverseFunc func = nullptr) const;
    };

    template<typename T>
    inline MinHeap<T> &MinHeap<T>::operator=(const MinHeap<T> &heap) {
        delete[] pArray;
        pArray = new T *[heap.mCapacity];
        mCapacity = heap.mCapacity;
        mSize = heap.mSize;
        mComparator = heap.mComparator;
        for (size_t i = 0; i < heap.mSize; ++i)
            pArray[i] = heap.pArray[i];
        return *this;
    }

    template<typename T>
    inline MinHeap<T> &MinHeap<T>::operator=(MinHeap<T> &&heap) noexcept {
        delete[] pArray;
        pArray = heap.pArray;
        mCapacity = heap.mCapacity;
        mSize = heap.mSize;
        mComparator = heap.mComparator;
        heap.pArray = nullptr;
        heap.mSize = 0;
        return *this;
    }

    template<typename T>
    inline MinHeap<T>::MinHeap(T **array, size_t size, Comparator comparator) {
        mComparator = comparator;
        if (array == nullptr || size == 0) {
            pArray = new T *[DEFAULT_CAPACITY];
            mCapacity = DEFAULT_CAPACITY;
        } else {
            mSize = size;
            mCapacity = max(size, DEFAULT_CAPACITY);
            pArray = new T *[mCapacity];
            for (size_t i = 0; i < size; ++i)
                pArray[i] = array[i];
            heapify();
        }
    }

    template<typename T>
    inline void MinHeap<T>::add(T *data) {
        not_null_check(data);
        ensuremCapacity();
        pArray[mSize++] = data;
        sift_up(mSize - 1);
    }

    template<typename T>
    inline T *MinHeap<T>::remove() {
        heap_empty_check();
        size_t last = --mSize;
        T *root = pArray[0];
        pArray[0] = pArray[last];
        pArray[last] = nullptr;
        sift_down(0);
        return root;
    }

    template<typename T>
    inline T *MinHeap<T>::replace(T *data) {
        not_null_check(data);
        T *root = nullptr;
        if (mSize == 0) {
            pArray[0] = data;
            mSize++;
        } else {
            root = pArray[0];
            pArray[0] = data;
            sift_down(0);
        }
        return root;
    }

    template<typename T>
    inline void MinHeap<T>::traverse(TraverseFunc func) const {
        if (mSize > 0) {
            int index = 0, lv_cnt = 1;
            queue<T *> q;
            q.push(pArray[index]);
            while (!q.empty()) {
                size_t left = (index << 1) + 1, right = left + 1;
                lv_cnt--;
                index++;
                T *data = q.front();
                q.pop();
                if (left < mSize)
                    q.push(pArray[left]);
                if (right < mSize)
                    q.push(pArray[right]);
                if (func != nullptr)
                    func(data);
                else
                    cout << *data << "\t";
                if (lv_cnt == 0) {
                    lv_cnt = q.size();
                    cout << "\n";
                }
            }
        }
    }

    template<typename T>
    inline void MinHeap<T>::ensuremCapacity() {
        if (mSize >= mCapacity) {
            T **old = pArray;
            mCapacity <<= 1;
            pArray = new T *[mCapacity];
            for (size_t i = 0; i < mSize; ++i)
                pArray[i] = old[i];
            delete[] old;
        }
    }

    template<typename T>
    inline void MinHeap<T>::sift_up(int index) {
        T *child = pArray[index];
        while (index > 0) {
            int parent_index = (index - 1) >> 1;
            T *parent = pArray[parent_index];
            if (compare(child, parent) > 0)
                break;
            pArray[index] = parent;
            index = parent_index;
        }
        pArray[index] = child;
    }

    template<typename T>
    inline void MinHeap<T>::sift_down(int index) {
        T *parent = pArray[index];
        int half = mSize >> 1;
        while (index < half) {
            int child_index = (index << 1) + 1, right_index = child_index + 1;
            T *child = pArray[child_index];
            if (right_index < mSize && compare(pArray[child_index], pArray[right_index]) >= 0)
                child = pArray[child_index = right_index];
            if (compare(parent, child) < 0)
                break;
            pArray[index] = child;
            index = child_index;
        }
        pArray[index] = parent;
    }
} // namespace app

#endif /* MIN_HEAP_HPP */
