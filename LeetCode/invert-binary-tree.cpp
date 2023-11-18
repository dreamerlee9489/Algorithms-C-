/**
 * @file invert-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 226. 翻转二叉树
 * @version 0.1
 * @date 2022-08-16
 * @link https://leetcode.cn/problems/invert-binary-tree/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

class Solution {
	void dfs(TreeNode* node) {
		if (node != nullptr) {
			TreeNode* temp = node->left;
			node->left = node->right;
			node->right = temp;
			dfs(node->left);
			dfs(node->right);
		}
	}

public:
	TreeNode* invertTree(TreeNode* root) {
		dfs(root);
		return root;
	}
};