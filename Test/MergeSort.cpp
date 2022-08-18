/**
 * @file MergeSort.cpp
 * @author your name (you@domain.com)
 * @brief 归并排序
 * @version 0.1
 * @date 2022-08-18
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <utility>
#include <vector>

class MergeSort {
  std::vector<int> array, left, right;

  void merge(int begin, int mid, int end) {
    int li = 0, le = mid - begin;
    int ri = 0, re = end - mid;
    int ai = begin;
    for (int i = li; i < le; i++) {
      left[i] = array[begin + i];
    }
    for (int i = ri; i < re; i++) {
      right[i] = array[mid + i];
    }
    while (li < le) {
      if (ri < re && right[ri] < left[li]) {
        array[ai++] = right[ri++];
      } else {
        array[ai++] = left[li++];
      }
    }
  }

  void divide(int begin, int end) {
    if (end - begin > 1) {
      int mid = (begin + end) >> 1;
      divide(begin, mid);
      divide(mid, end);
      merge(begin, mid, end);
    }
  }

public:
  MergeSort(std::vector<int> &array) {
    left = std::vector<int>(array.size() >> 1);
    right = std::vector<int>(array.size() - left.size());
    this->array = std::move(array);
  }

  ~MergeSort() = default;

  std::vector<int> &sort() {
    divide(0, array.size());
    return array;
  }
};

int main(int argc, char const *argv[]) {
  std::vector<int> array = {50, 21, 80, 43, 38, 14, 70, 15};
  array = MergeSort(array).sort();
  for (int i : array) {
    std::cout << i << " ";
  }
  return 0;
}
