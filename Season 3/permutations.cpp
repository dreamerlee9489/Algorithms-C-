/**
 * @file permutations.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 46. 全排列
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode.cn/problems/permutations/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
using namespace std;

/**
 * 解题技巧总结：
 * 全排列问题是一个典型的回溯算法应用场景，以下是解题时应该考虑的要点：
 * 回溯框架：实现一个回溯函数，它将维护当前状态（包括已经选择的数字和还未选择的数字），并在符合条件时进行递归，以探索所有可能的情况。
 * 递归和终止条件：递归需要一个终止条件，对于全排列问题，当当前排列的长度等于输入数组的长度时，表示一个全排列已经形成，此时应记录当前排列，并返回上一层递归。
 * 维护状态：为了防止在同一个排列中使用相同的数字，需要维护一个状态来标记已经使用过的数字。
 * 不重复使用数字：因为题目中提到数组不含重复数字，所以在递归过程中直接使用一个额外的数据结构（如布尔数组或哈希集合）来记录哪些数字已经被使用过，从而避免重复使用同一个数字。
 * 时间复杂度：对于不重复数字的全排列问题，时间复杂度为O(n!)，其中n是数组的长度，因为需要探索n!种可能的排列。
 * 
 */
class Solution {
public:
	void backtrack(vector<int>& nums, vector<vector<int>>& res, vector<int>& permutation, vector<bool>& used) {
		if (permutation.size() == nums.size()) {
			// 当前排列长度等于nums长度，记录当前排列
			res.push_back(permutation);
			return;
		}

		for (int i = 0; i < nums.size(); ++i) {
			// 跳过已经使用过的数字
			if (used[i]) continue;
			// 做选择
			permutation.push_back(nums[i]);
			used[i] = true;
			// 进入下一层决策树
			backtrack(nums, res, permutation, used);
			// 撤销选择
			permutation.pop_back();
			used[i] = false;
		}
	}

	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int>> res;
		vector<int> permutation;
		vector<bool> used(nums.size(), false);
		backtrack(nums, res, permutation, used);
		return res;
	}
};