/**
 * @file jump-game.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 55. 跳跃游戏
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/jump-game/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	bool canJump(vector<int>& nums) {
		int reach = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (i > reach)
				return false;
			reach = max(reach, i + nums[i]);
		}
		return true;
	}
};