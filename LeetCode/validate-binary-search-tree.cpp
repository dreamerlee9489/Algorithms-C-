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

using namespace std;

class Solution {
	vector<int> mVec;

	void inorder(TreeNode* node) {
		if (node != nullptr) {
			inorder(node->left);
			mVec.emplace_back(node->val);
			inorder(node->right);
		}
	}

public:
	bool isValidBST(TreeNode* root) {
		inorder(root);
		for (size_t i = 1; i < mVec.size(); i++)
			if (mVec[i - 1] > mVec[i])
				return false;
		return true;
	}
};