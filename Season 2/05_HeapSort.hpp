#ifndef HEAP_SORT_HPP
#define HEAP_SORT_HPP

#include "./01_ISort.hpp"

namespace app {
    /**
     * @brief 堆排序
     * @date 2022-04-27
     * @tparam T
     */
    template<typename T>
    class HeapSort : public ISort<T> {
        size_t _heapmSize = 0;

        void sift_down(size_t index) {
            T data = this->pArray[index];
            size_t half = _heapmSize >> 1;
            while (index < half) {
                size_t child_index = (index << 1) + 1;
                T child = this->pArray[child_index];
                size_t right_index = child_index + 1;
                if (right_index < _heapmSize && this->compare(this->pArray[right_index], child) > 0)
                    child = this->pArray[child_index = right_index];
                if (this->compare(data, child) >= 0)
                    break;
                this->pArray[index] = child;
                index = child_index;
            }
            this->pArray[index] = data;
        }

        void sort_algorithm() override {
            _heapmSize = this->mSize;
            for (int i = (_heapmSize >> 1) - 1; i >= 0; --i)
                sift_down(i);
            while (_heapmSize > 1) {
                this->swap(0, --_heapmSize);
                sift_down(0);
            }
        }

    public:
        HeapSort() = default;

        ~HeapSort() = default;
    };
} // namespace app

#endif /* HEAP_SORT_HPP */
