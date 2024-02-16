/**
 * @file validate-binary-search-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 98. 验证二叉搜索树
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/validate-binary-search-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <vector>
#include <climits>
using namespace std;

class Solution {
	bool isValidBST(TreeNode* root, long min, long max) {
		if (root == nullptr) return true;
		if (root->val <= min || root->val >= max) return false;
		return isValidBST(root->left, min, root->val) && isValidBST(root->right, root->val, max);
	}

public:
	bool isValidBST(TreeNode* root) {
		return isValidBST(root, LONG_MIN, LONG_MAX);
	}
};