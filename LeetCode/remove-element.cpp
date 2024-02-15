/**
 * @file remove-element.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 27. 移除元素
 * @version 0.1
 * @date 2024-02-14
 * @link https://leetcode.cn/problems/remove-element/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
using namespace std;

class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		int count = 0, left = 0, right = 0;
		for (int i = 0; i < nums.size(); i++)
			if (nums[i] == val) ++count;
		if (count == 0) return nums.size();
		while (left < nums.size() - count) {
			if (nums[left] != val) {
				++left;
				continue;
			}
			right = left + 1;
			while (nums[left] == nums[right]) ++right;
			int tmp = nums[left];
			nums[left] = nums[right];
			nums[right] = tmp;
		}
		return nums.size() - count;
	}
};