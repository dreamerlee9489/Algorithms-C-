/**
 * @file HeapSort.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 堆排序
 * @version 0.1
 * @date 2022-08-18
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <utility>
#include <vector>

class HeapSort {
	std::vector<int> array;
	int len = 0;

	void swap(int lhs, int rhs) {
		int temp = array[lhs];
		array[lhs] = array[rhs];
		array[rhs] = temp;
	}

	void siftdown(int i) {
		int data = array[i];
		int half = len >> 1;
		while (i < half) {
			int left = (i << 1) + 1, right = left + 1 < len ? left + 1 : left;
			int max = array[left] < array[right] ? right : left;
			if (data >= array[max])
				break;
			array[i] = array[max];
			i = max;
		}
		array[i] = data;
	}

	void heapify() {
		for (int i = (len >> 1) - 1; i >= 0; --i) {
			siftdown(i);
		}
	}

public:
	HeapSort(std::vector<int>& array) {
		this->len = array.size();
		this->array = std::move(array);
	}

	~HeapSort() = default;

	std::vector<int>& sort() {
		heapify();
		while (len > 1) {
			swap(0, --len);
			siftdown(0);
		}
		return array;
	}
};

int main(int argc, char const* argv[]) {
	std::vector<int> array = { 50, 21, 80, 43, 38, 14, 70, 15 };
	array = HeapSort(array).sort();
	for (int i : array) {
		std::cout << i << " ";
	}
	return 0;
}
