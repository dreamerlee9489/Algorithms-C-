/**
 * @file move-zeroes.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 283. 移动零
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/move-zeroes/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		if (nums.empty())
			return;
		for (size_t i = 0, cur = 0; i < nums.size(); i++) {
			if (nums[i] != 0) {
				if (i != cur) {
					nums[cur] = nums[i];
					nums[i] = 0;
				}
				cur++;
			}
		}
	}
};