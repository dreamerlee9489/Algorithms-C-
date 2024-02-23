/**
 * @file invert-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 226. 翻转二叉树
 * @version 0.1
 * @date 2022-04-05
 * @link https://leetcode-cn.com/problems/invert-binary-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

 /**
  * 翻转一棵二叉树是一个经典的递归问题。它的基本思想是将每个节点的左右子树进行交换。递归的基本情况是遇到空节点，这时候不需要做任何操作。对于非空节点，我们先翻转其左子树和右子树，然后交换它们。
  * 解题技巧总结：
  * 使用递归函数，针对给定的节点进行翻转操作。
  * 如果当前节点为nullptr，返回nullptr。
  * 递归翻转当前节点的左子树和右子树。
  * 将当前节点的左子树指针指向原右子树的翻转结果，将右子树指针指向原左子树的翻转结果。
  * 返回当前节点作为新的根节点。
  *
  */
class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) {
			return nullptr;
		}
		// 翻转左右子树
		TreeNode* left = invertTree(root->left);
		TreeNode* right = invertTree(root->right);
		// 交换左右子树
		root->left = right;
		root->right = left;
		return root;
	}
};