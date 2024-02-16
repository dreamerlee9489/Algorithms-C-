/**
 * @file path-sum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 112. 路径总和
 * @version 0.1
 * @date 2024-02-16
 * @link https://leetcode.cn/problems/path-sum/description/
 * @copyright Copyright (c) 2024
 *
 */
#include "./TreeNode.hpp"

class Solution {
public:
	bool hasPathSum(TreeNode* root, int targetSum) {
		if (!root) return false;
		if (!root->left && !root->right && targetSum - root->val == 0) return true;
		return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
	}
};