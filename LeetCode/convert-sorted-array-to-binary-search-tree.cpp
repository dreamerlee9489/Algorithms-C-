/**
 * @file convert-sorted-array-to-binary-search-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 108. 将有序数组转换为二叉搜索树
 * @version 0.1
 * @date 2022-08-10
 * @link
 * https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/
 * @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <vector>

using namespace std;

class Solution {
	TreeNode* buildTree(int begin, int end, vector<int>& nums) {
		if (begin > end)
			return nullptr;
		int mid = (begin + end) / 2;
		TreeNode* root = new TreeNode(nums[mid]);
		root->left = buildTree(begin, mid - 1, nums);
		root->right = buildTree(mid + 1, end, nums);
		return root;
	}

public:
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return buildTree(0, nums.size() - 1, nums);
	}
};