/**
 * @file kth-largest-element-in-an-array.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 215. 数组中的第K个最大元素
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/kth-largest-element-in-an-array/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int> que;
		for (int i = 0; i < nums.size(); i++)
			que.emplace(nums[i]);
		for (int i = 1; i < k; i++)
			que.pop();
		return que.top();
	}
};