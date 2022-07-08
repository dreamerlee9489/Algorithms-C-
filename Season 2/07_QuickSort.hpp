#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP
#include <random>
#include "./01_ISort.hpp"

namespace app
{
    /**
     * @brief 快速排序
     * @date 2022-04-27
     * @tparam T
     */
    template <typename T>
    class QuickSort : public ISort<T>
    {
        size_t pivot_index(size_t beg, size_t end)
        {
            static uniform_int_distribution<size_t> u(0, end - beg);
            static default_random_engine e;
            // this->swap(beg, beg + u(e));
            T pivot = this->_array[beg];
            end--;
            while (beg < end)
            {
                while (beg < end)
                {
                    if (this->compare(pivot, this->_array[end]) < 0)
                        end--;
                    else
                    {
                        this->_array[beg++] = this->_array[end];
                        break;
                    }
                }
                while (beg < end)
                {
                    if (this->compare(pivot, this->_array[beg]) > 0)
                        beg++;
                    else
                    {
                        this->_array[end--] = this->_array[beg];
                        break;
                    }
                }
            }
            this->_array[beg] = pivot;
            return beg;
        }
        void quick_sort(size_t beg, size_t end)
        {
            if (end - beg > 1)
            {
                size_t mid = pivot_index(beg, end);
                quick_sort(beg, mid);
                quick_sort(mid + 1, end);
            }
        }
        void sort_algorithm() override { quick_sort(0, this->_size); }

    public:
        QuickSort() = default;
        ~QuickSort() = default;
    };
} // namespace app

#endif /* QUICK_SORT_HPP */
