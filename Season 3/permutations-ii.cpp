/**
 * @file permutations-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 47. 全排列 II
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode.cn/problems/permutations-ii/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
	void dfs(int index, vector<int>& nums, vector<vector<int>>& list) {
		if (index == nums.size()) {
			list.emplace_back(nums);
			return;
		}
		for (int i = index; i < nums.size(); ++i) {
			if (!isRepeat(nums, index, i)) {
				swap(nums, index, i);
				dfs(index + 1, nums, list);
				swap(nums, index, i);
			}
		}
	}

	void swap(vector<int>& nums, int i, int j) {
		int temp = nums[i];
		nums[i] = nums[j];
		nums[j] = temp;
	}

	bool isRepeat(vector<int>& nums, int index, int i) {
		for (int j = index; j < i; ++j)
			if (nums[j] == nums[i])
				return true;
		return false;
	}

public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		if (nums.empty())
			return vector<vector<int>>();
		vector<vector<int>> list;
		dfs(0, nums, list);
		return list;
	}
};