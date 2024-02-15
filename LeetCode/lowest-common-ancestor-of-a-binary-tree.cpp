/**
 * @file lowest-common-ancestor-of-a-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 236. 二叉树的最近公共祖先
 * @version 0.1
 * @date 2022-08-08
 * @link https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// 找到p,q
		if (root == nullptr || root == p || root == q)
			return root;
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);
		// p,q分别为左右子结点
		if (left != nullptr && right != nullptr)
			return root;
		// p,q在同一颗子树
		return left != nullptr ? left : right;
	}
};