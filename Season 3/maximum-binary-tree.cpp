/**
 * @file maximum-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 654. 最大二叉树
 * @version 0.1
 * @date 2022-07-19
 * @link https://leetcode.cn/problems/maximum-binary-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <vector>
using namespace std;

/**
 * 解题技巧总结：
 * 找到最大值：在给定的数组nums中找到最大值及其索引，这将成为当前二叉树的根节点。
 * 递归构建：使用找到的最大值将数组分为左右两部分。左边的部分用于递归构建左子树，右边的部分用于递归构建右子树。
 * 数组分割：在递归过程中，每次传递给递归函数的是当前考虑的子数组的范围，而不是复制子数组本身，这样可以减少不必要的内存使用和复制开销。
 * 递归基：当子数组为空时，返回nullptr，表示当前子树不存在。
 * 树节点定义：定义二叉树节点的结构体，包含值、左孩子指针和右孩子指针。
 * 辅助函数：编写一个辅助函数，它接受当前子数组的左右边界作为参数，这样可以在递归调用时只考虑数组的一部分。
 * 分治思想：该问题的核心是分治思想，每次递归调用都会解决当前子问题，并以此构建出整个问题的解。
 *
 */
class Solution {
public:
	TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
		return buildTree(nums, 0, nums.size());
	}

	TreeNode* buildTree(vector<int>& nums, int l, int r) {
		if (l == r) return nullptr;

		// 找到最大值及其索引
		int max_i = l;
		for (int i = l; i < r; ++i) {
			if (nums[i] > nums[max_i]) max_i = i;
		}

		TreeNode* root = new TreeNode(nums[max_i]);
		// 递归构建左右子树
		root->left = buildTree(nums, l, max_i);
		root->right = buildTree(nums, max_i + 1, r);

		return root;
	}
};