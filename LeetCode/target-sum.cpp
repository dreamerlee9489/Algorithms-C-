/**
 * @file target-sum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 494. 目标和
 * @version 0.1
 * @date 2024-02-16
 * @link https://leetcode.cn/problems/target-sum/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
using namespace std;

class Solution {
	int count = 0;

	void backtrace(vector<int>& nums, int target, int index, int sum) {
		if (index == nums.size()) {
			if (sum == target) ++count;
		}
		else {
			backtrace(nums, target, index + 1, sum + nums[index]);
			backtrace(nums, target, index + 1, sum - nums[index]);
		}
	}

public:
	int findTargetSumWays(vector<int>& nums, int target) {
		backtrace(nums, target, 0, 0);
		return count;
	}
};