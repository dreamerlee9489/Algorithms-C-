#ifndef QUICK_SORT_HPP
#define QUICK_SORT_HPP

#include "./01_ISort.hpp"
#include <random>

namespace app {
/**
 * @brief 快速排序
 * @date 2022-04-27
 * @tparam T
 */
template <typename T> class QuickSort : public ISort<T> {
  uniform_int_distribution<size_t> u;
  default_random_engine e;

  size_t pivot_index(size_t beg, size_t end) {
    // 轴心最终位置恰为beg时, 快排降为O(n^2)
    u = uniform_int_distribution<size_t>(beg, --end); // 均匀整数分布
    this->swap(beg, u(e));
    T pivot = this->_array[beg];
    while (beg < end) {
      while (beg < end) {
        // 若元素值相等, <=导致轴心最终位置恰为beg
        if (this->compare(pivot, this->_array[end]) < 0)  
          end--;
        else {
          this->_array[beg++] = this->_array[end];
          break;
        }
      }
      while (beg < end) {
        // 若元素值相等, >=导致轴心最终位置恰为beg
        if (this->compare(pivot, this->_array[beg]) > 0)  
          beg++;
        else {
          this->_array[end--] = this->_array[beg];
          break;
        }
      }
    }
    this->_array[beg] = pivot;  // beg = end
    return beg;
  }

  void quick_sort(size_t beg, size_t end) {
    if (end - beg > 1) {
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
