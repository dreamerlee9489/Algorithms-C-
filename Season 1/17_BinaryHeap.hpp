#ifndef BINARY_HEAP_HPP
#define BINARY_HEAP_HPP

#include "./17_IHeap.hpp"

namespace app {
    /**
     * @brief 二叉堆
     * @date 2022-04-22
     * @tparam T
     */
    template<typename T>
    class BinaryHeap : public IHeap<T> {
        const size_t DEFAULT_CAPACITY = 8;
        size_t mCapacity = 0;
        shared_ptr<T> *pArray = nullptr;

        void ensuremCapacity();

        void sift_up(int index);

        void sift_down(int index);

        void heapify() {
            for (int i = (this->mSize >> 1) - 1; i >= 0; --i)
                sift_down(i);
        }

        void heap_empty_check() const {
            if (this->mSize == 0)
                throw out_of_range("heap is empty.");
        }

        void not_null_check(shared_ptr<T> data) const {
            if (data == nullptr)
                throw invalid_argument("data must be not null.");
        }

    public:
        BinaryHeap<T> &operator=(const BinaryHeap<T> &heap);

        BinaryHeap<T> &operator=(BinaryHeap<T> &&heap) noexcept;

        BinaryHeap(typename IHeap<T>::Comparator comparator = nullptr, shared_ptr<T> *array = nullptr, size_t size = 0);

        BinaryHeap(const BinaryHeap<T> &heap) { *this = heap; }

        BinaryHeap(BinaryHeap<T> &&heap) noexcept { *this = move(heap); }

        ~BinaryHeap() { delete[] pArray; }

        size_t capacity() const { return mCapacity; }

        void add(shared_ptr<T> data) override;

        shared_ptr<T> remove() override;

        shared_ptr<T> replace(shared_ptr<T> data) override;

        shared_ptr<T> get() const override {
            heap_empty_check();
            return pArray[0];
        }

        void clear() override {
            for (size_t i = 0; i < mCapacity; ++i)
                pArray[i] = nullptr;
            this->mSize = 0;
        }

        void traverse(typename IHeap<T>::TraverseFunc func = nullptr) const override;
    };

    template<typename T>
    inline BinaryHeap<T> &BinaryHeap<T>::operator=(const BinaryHeap<T> &heap) {
        delete[] pArray;
        pArray = new shared_ptr<T>[heap.mCapacity];
        mCapacity = heap.mCapacity;
        this->mSize = heap.mSize;
        this->mComparator = heap.mComparator;
        for (size_t i = 0; i < heap.mSize; ++i)
            pArray[i] = heap.pArray[i];
        return *this;
    }

    template<typename T>
    inline BinaryHeap<T> &BinaryHeap<T>::operator=(BinaryHeap<T> &&heap) noexcept {
        delete[] pArray;
        pArray = heap.pArray;
        mCapacity = heap.mCapacity;
        this->mSize = heap.mSize;
        this->mComparator = heap.mComparator;
        heap.pArray = nullptr;
        heap.mSize = 0;
        return *this;
    }

    template<typename T>
    inline
    BinaryHeap<T>::BinaryHeap(typename IHeap<T>::Comparator comparator, shared_ptr<T> *array, size_t size) : IHeap<T>(
            comparator) {
        if (array == nullptr || size == 0) {
            pArray = new shared_ptr<T>[DEFAULT_CAPACITY];
            mCapacity = DEFAULT_CAPACITY;
        } else {
            this->mSize = size;
            mCapacity = max(size, DEFAULT_CAPACITY);
            pArray = new shared_ptr<T>[mCapacity];
            for (size_t i = 0; i < size; ++i)
                pArray[i] = array[i];
            heapify();
        }
    }

    template<typename T>
    inline void BinaryHeap<T>::add(shared_ptr<T> data) {
        not_null_check(data);
        ensuremCapacity();
        pArray[this->mSize++] = data;
        sift_up(this->mSize - 1);
    }

    template<typename T>
    inline shared_ptr<T> BinaryHeap<T>::remove() {
        heap_empty_check();
        size_t last = --this->mSize;
        shared_ptr<T> root = pArray[0];
        pArray[0] = pArray[last];
        pArray[last] = nullptr;
        sift_down(0);
        return root;
    }

    template<typename T>
    inline shared_ptr<T> BinaryHeap<T>::replace(shared_ptr<T> data) {
        not_null_check(data);
        shared_ptr<T> root = nullptr;
        if (this->mSize == 0) {
            pArray[0] = data;
            this->mSize++;
        } else {
            root = pArray[0];
            pArray[0] = data;
            sift_down(0);
        }
        return root;
    }

    template<typename T>
    inline void BinaryHeap<T>::traverse(typename IHeap<T>::TraverseFunc func) const {
        if (this->mSize > 0) {
            int index = 0, lv_cnt = 1;
            queue<shared_ptr<T>> q;
            q.push(pArray[index]);
            while (!q.empty()) {
                size_t left = (index << 1) + 1, right = left + 1;
                lv_cnt--;
                index++;
                shared_ptr<T> data = q.front();
                q.pop();
                if (left < this->mSize)
                    q.push(pArray[left]);
                if (right < this->mSize)
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
    inline void BinaryHeap<T>::ensuremCapacity() {
        if (this->mSize >= mCapacity) {
            shared_ptr<T> *old = pArray;
            mCapacity <<= 1;
            pArray = new shared_ptr<T>[mCapacity];
            for (size_t i = 0; i < this->mSize; ++i)
                pArray[i] = old[i];
            delete[] old;
        }
    }

    template<typename T>
    inline void BinaryHeap<T>::sift_up(int index) {
        shared_ptr<T> child = pArray[index];
        while (index > 0) {
            int parent_index = (index - 1) >> 1;
            shared_ptr<T> parent = pArray[parent_index];
            if (this->compare(child, parent) <= 0)
                break;
            pArray[index] = parent;
            index = parent_index;
        }
        pArray[index] = child;
    }

    template<typename T>
    inline void BinaryHeap<T>::sift_down(int index) {
        shared_ptr<T> parent = pArray[index];
        int half = this->mSize >> 1;
        while (index < half) {
            int child_index = (index << 1) + 1, right_index = child_index + 1;
            shared_ptr<T> child = pArray[child_index];
            if (right_index < this->mSize && this->compare(pArray[child_index], pArray[right_index]) < 0)
                child = pArray[child_index = right_index];
            if (this->compare(parent, child) >= 0)
                break;
            pArray[index] = child;
            index = child_index;
        }
        pArray[index] = parent;
    }
} // namespace app

#endif /* BINARY_HEAP_HPP */
