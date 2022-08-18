/**
 * @file QuickSort.cpp
 * @author your name (you@domain.com)
 * @brief 快速排序
 * @version 0.1
 * @date 2022-08-18
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <random>
#include <utility>
#include <vector>

class QuickSort {
  std::vector<int> array;
  std::uniform_int_distribution<int> d;
  std::default_random_engine e;

  void swap(int lhs, int rhs) {
    int temp = array[lhs];
    array[lhs] = array[rhs];
    array[rhs] = temp;
  }

  int pivotIndex(int begin, int end) {
    d = std::uniform_int_distribution<int>(begin, --end);
    swap(begin, d(e));
    int pivot = array[begin];
    while (begin < end) {
      while (begin < end) {
        if (pivot < array[end]) {
          --end;
        } else {
          array[begin++] = array[end];
          break;
        }
      }
      while (begin < end) {
        if (array[begin] < pivot) {
          ++begin;
        } else {
          array[end--] = array[begin];
          break;
        }
      }
    }
    array[begin] = pivot;
    return begin;
  }

  void sort(int begin, int end) {
    if (end - begin > 1) {
      int mid = pivotIndex(begin, end);
      sort(begin, mid);
      sort(mid + 1, end);
    }
  }

public:
  QuickSort(std::vector<int> &array) { this->array = std::move(array); }

  ~QuickSort() = default;

  std::vector<int> &sort() {
    sort(0, array.size());
    return array;
  }
};

int main(int argc, char const *argv[]) {
  std::vector<int> array = {50, 21, 80, 43, 38, 14, 70, 15};
  array = QuickSort(array).sort();
  for (int i : array) {
    std::cout << i << " ";
  }
  return 0;
}
