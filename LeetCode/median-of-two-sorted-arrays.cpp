/**
 * @file median-of-two-sorted-arrays.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 4. 寻找两个正序数组的中位数
 * @version 0.1
 * @date 2022-07-30
 * @link https://leetcode.cn/problems/median-of-two-sorted-arrays/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
	size_t pivot_index(vector<int>& nums, size_t begin, size_t end) {
		default_random_engine e;
		uniform_int_distribution<size_t> d(0, end - begin);
		size_t index = begin + d(e);
		int temp = nums[begin];
		nums[begin] = nums[index];
		nums[index] = temp;

		int pivot = nums[begin];
		end--;
		while (begin < end) {
			while (begin < end) {
				// 在轴心右侧找到第一个小于轴心的元素，将其置于begin
				if (nums[end] >= pivot)
					end--;
				else {
					nums[begin++] = nums[end];
					break;
				}
			}
			while (begin < end) {
				// 在轴心左侧找到第一个大于轴心的元素，将其置于end
				if (nums[begin] <= pivot)
					begin++;
				else {
					nums[end--] = nums[begin];
					break;
				}
			}
		}
		nums[begin] = pivot;
		return begin;
	}

	void quick_sort(vector<int>& nums, size_t begin, size_t end) {
		if (end - begin > 1) {
			size_t mid = pivot_index(nums, begin, end);
			quick_sort(nums, begin, mid);
			quick_sort(nums, mid + 1, end);
		}
	}

public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		nums1.resize(nums1.size() + nums2.size());
		for (size_t i = 0; i < nums2.size(); i++)
			nums1[nums1.size() - nums2.size() + i] = nums2[i];
		// sort(nums1.begin(), nums1.end());
		quick_sort(nums1, 0, nums1.size());
		size_t mid = nums1.size() / 2;
		return (nums1.size() & 1) == 1 ? nums1[mid]
			: ((nums1[mid - 1] + nums1[mid]) / 2.0);
	}
};

int main(int argc, char const* argv[]) {
	vector<int> nums1 = { 1, 3, 5, 7, 9 };
	vector<int> nums2 = { 0, 2, 4, 6, 8 };
	cout << Solution().findMedianSortedArrays(nums1, nums2) << "\n";
	vector<int> nums3 = { 1, 3 };
	vector<int> nums4 = { 2 };
	cout << Solution().findMedianSortedArrays(nums3, nums4) << "\n";
	vector<int> nums5 = { 1, 2 };
	vector<int> nums6 = { 3, 4 };
	cout << Solution().findMedianSortedArrays(nums5, nums6) << "\n";
	return 0;
}