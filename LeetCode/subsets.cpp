/**
 * @file subsets.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 78. 子集
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/subsets/
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
	vector<int> tmp;
	vector<vector<int>> res;

	void dfs(int layer, vector<int>& nums) {
		if (layer == nums.size()) {
			res.emplace_back(tmp);
			return;
		}
		tmp.push_back(nums[layer]);
		dfs(layer + 1, nums);
		tmp.pop_back();
		dfs(layer + 1, nums);
	}

public:
	vector<vector<int>> subsets(vector<int>& nums) {
		dfs(0, nums);
		return res;
	}
};

int main(int argc, char const* argv[]) {
	vector<int> nums = { 1, 2, 3 };
	auto res = Solution().subsets(nums);
	return 0;
}
