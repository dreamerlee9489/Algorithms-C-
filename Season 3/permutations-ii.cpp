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
#include <algorithm>
using namespace std;

/**
 * 解题技巧总结：
 * 为了解决这个问题，需要注意以下几个方面：
 * 排序：首先对数组进行排序，这样可以让重复的数字聚集在一起，便于后续处理。
 * 回溯法：使用回溯法遍历所有可能的排列情况。回溯法是一种通过递归来实现的算法，用于在解空间树中深度优先搜索问题的所有解。
 * 剪枝：为了避免生成重复的排列，需要在回溯的过程中进行剪枝操作。当当前数字与前一个数字相同，并且前一个数字还没有被使用过的时候，跳过当前的数字。
 * 维护状态：使用一个辅助数组或者状态变量来记录哪些数字已经被使用过，从而避免在同一位置重复放置相同的数字。
 * 构建排列：构建排列时，每次都从头搜索尚未使用的数字，将其加入到当前排列中，然后继续递归处理下一个位置。
 * 时间复杂度：问题的时间复杂度取决于生成的排列数量和单个排列的长度。通常，复杂度为O(n*n!)，其中n是数组的长度。
 *
 */
class Solution {
public:
	void backtrack(vector<int>& nums, int start, vector<vector<int>>& res, vector<int>& permutation, vector<bool>& used) {
		if (start == nums.size()) {
			res.push_back(permutation);
			return;
		}

		for (int i = 0; i < nums.size(); ++i) {
			// 剪枝：跳过已经使用过的数字或者相同的数字
			if (used[i] || (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])) {
				continue;
			}
			used[i] = true;
			permutation[start] = nums[i];
			backtrack(nums, start + 1, res, permutation, used);
			used[i] = false; // 回溯
		}
	}

	vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> res;
		vector<int> permutation(nums.size());
		vector<bool> used(nums.size(), false);
		sort(nums.begin(), nums.end()); // 排序以方便剪枝
		backtrack(nums, 0, res, permutation, used);
		return res;
	}
};