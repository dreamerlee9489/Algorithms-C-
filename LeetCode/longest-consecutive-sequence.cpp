/**
 * @file longest-consecutive-sequence.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 128. 最长连续序列
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/longest-consecutive-sequence/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int count = 1, maxCount = 1;
		sort(nums.begin(), nums.end());
		for (int i = 1; i < nums.size(); i++) {
			if (nums[i] == nums[i - 1])
				continue;
			if (nums[i] == nums[i - 1] + 1)
				maxCount = max(++count, maxCount);
			else
				count = 1;
		}
		return maxCount;
	}
};