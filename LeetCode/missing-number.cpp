/**
 * @file missing-number.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 268. 丢失的数字
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/missing-number/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	int missingNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); i++)
			if (nums[i] != i)
				return i;
		return nums.size();
	}
};