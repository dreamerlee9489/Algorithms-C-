/**
 * @file construct-binary-tree-from-preorder-and-inorder-traversal.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 105. 从前序与中序遍历序列构造二叉树
 * @version 0.1
 * @date 2022-08-08
 * @link https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
	unordered_map<int, int> inMap;

	TreeNode* buildTree(std::vector<int>& preorder, int preBeg, int preEnd, std::vector<int>& inorder, int inBeg, int inEnd) {
		if (preBeg > preEnd || inBeg > inEnd) return nullptr;
		TreeNode* root = new TreeNode(preorder[preBeg]);
		int inRoot = inMap[root->val];
		int leftCnt = inRoot - inBeg;
		root->left = buildTree(preorder, preBeg + 1, preBeg + leftCnt, inorder, inBeg, inRoot - 1);
		root->right = buildTree(preorder, preBeg + leftCnt + 1, preEnd, inorder, inRoot + 1, inEnd);
		return root;
	}

public:
	TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
		for (int i = 0; i < inorder.size(); i++) inMap[inorder[i]] = i;
		return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
	}
};