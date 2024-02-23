/**
 * @file recover-binary-search-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 99. 恢复二叉搜索树
 * @version 0.1
 * @date 2022-07-22
 * @link https://leetcode.cn/problems/recover-binary-search-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <algorithm>
using namespace std;

/**
 * 解题技巧总结：
 * 题目要求我们恢复一个因为两个节点值错误交换导致不再满足二叉搜索树性质的树。对于二叉搜索树，有一个重要的性质：中序遍历序列是递增的。因此，我们可以通过中序遍历来找到被错误交换的两个节点，然后恢复它们的值。
 * 以下是解题的关键步骤：
 * 中序遍历：进行中序遍历，记录遍历的结果。遍历过程中，应该可以发现序列中的异常（逆序对）。在标准的递增序列中，逆序对是不存在的，但在这个问题中，由于有两个元素的位置被错误交换了，所以会出现一到两个逆序对。
 * 寻找逆序对：在中序遍历的过程中，我们需要找到两个逆序对。第一个逆序对中较大的节点是第一个错误节点，第二个逆序对中较小的节点是第二个错误节点。如果只发现了一个逆序对，则这个逆序对中的两个节点就是被错误交换的节点。
 * 交换节点值：找到两个错误的节点之后，交换这两个节点的值，即可恢复二叉搜索树。
 * 空间优化：在实际实现时，可以不用额外的数组来存储中序遍历的结果，而是在遍历的过程中直接找逆序对。
 * 时间复杂度：本算法的时间复杂度为O(n)，其中n是树中节点的数量，因为我们需要遍历所有节点来找到被错误交换的节点。
 * 边界情况：特别注意树为空或只有一个节点的情况。
 *
 */
class Solution {
public:
	void recoverTree(TreeNode* root) {
		TreeNode* first = nullptr, * second = nullptr, * prev = nullptr;
		// 使用Morris中序遍历寻找逆序对
		TreeNode* current = root, * predecessor = nullptr;
		while (current != nullptr) {
			if (current->left == nullptr) {
				detect(prev, current, first, second);
				prev = current;
				current = current->right;
			}
			else {
				predecessor = current->left;
				while (predecessor->right != nullptr && predecessor->right != current) {
					predecessor = predecessor->right;
				}
				if (predecessor->right == nullptr) {
					predecessor->right = current;
					current = current->left;
				}
				else {
					predecessor->right = nullptr;
					detect(prev, current, first, second);
					prev = current;
					current = current->right;
				}
			}
		}
		// 交换两个节点的值来恢复二叉树
		if (first && second) {
			swap(first->val, second->val);
		}
	}

	void detect(TreeNode*& prev, TreeNode*& current, TreeNode*& first, TreeNode*& second) {
		if (prev != nullptr && prev->val > current->val) {
			if (first == nullptr) {
				first = prev;
			}
			// 第二个节点在这里被赋值，可能是相邻的逆序对的第二个节点，也可能是不相邻的逆序对的第二个节点
			second = current;
		}
	}
};