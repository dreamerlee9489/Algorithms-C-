/**
 * @file sort-colors.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 75. 颜色分类
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/sort-colors/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
	void swap(vector<int>& nums, int i, int j) {
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}

public:
	void sortColors(vector<int>& nums) {
		int i = 0, l = 0, r = nums.size() - 1;
		while (i <= r) {
			int v = nums[i];
			if (v == 0)
				swap(nums, i++, l++);
			else if (v == 1)
				i++;
			else
				swap(nums, i, r--);
		}
	}
};