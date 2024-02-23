/**
 * @file largest-bst-subtree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 333. 最大BST子树
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode-cn.com/problems/largest-bst-subtree/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <algorithm>
#include <climits>
using namespace std;

/**
 * 要解决这个问题，可以使用自底向上的递归方法。我们需要定义一个辅助数据结构来保存每个子树的相关信息，比如子树是否是BST、子树中的最大值和最小值以及子树的节点数量。通过这些信息，对每个节点，我们可以判断以该节点为根的子树是否是BST，以及它的大小。
 * 解题技巧总结：
 * 创建一个辅助数据结构来保存每个子树的信息：是否是BST、子树中最大最小值、子树节点数量。
 * 使用后序遍历（左右根的顺序）的方式递归处理每个节点，这样我们可以保证处理一个节点时，它的左右子树已经被处理过了。
 * 在每次递归中，判断左右子树是否是BST，并比较当前节点的值是否大于左子树的最大值且小于右子树的最小值。如果左右子树都是BST，并且当前节点的值满足BST的性质，那么以当前节点为根的子树也是BST。
 * 如果当前子树是BST，更新最大BST子树的大小以及对应的根节点。
 * 返回当前子树的信息给上一层递归。
 *
 */
class Solution {
public:
	struct SubtreeInfo {
		bool isBST;
		int size; // 节点数量
		int minVal; // 子树中的最小值
		int maxVal; // 子树中的最大值
	};

	SubtreeInfo findLargestBSTSubtree(TreeNode* root, int& maxSize, TreeNode*& largestBST) {
		if (!root) return { true, 0, INT_MAX, INT_MIN };

		auto leftInfo = findLargestBSTSubtree(root->left, maxSize, largestBST);
		auto rightInfo = findLargestBSTSubtree(root->right, maxSize, largestBST);

		SubtreeInfo currentInfo;
		currentInfo.isBST = leftInfo.isBST && rightInfo.isBST &&
			root->val > leftInfo.maxVal && root->val < rightInfo.minVal;

		if (currentInfo.isBST) {
			currentInfo.size = leftInfo.size + rightInfo.size + 1;
			currentInfo.minVal = min(root->val, leftInfo.minVal);
			currentInfo.maxVal = max(root->val, rightInfo.maxVal);

			if (currentInfo.size > maxSize) {
				maxSize = currentInfo.size;
				largestBST = root;
			}
		}
		else {
			currentInfo.size = 0; // If it's not a BST, size doesn't matter
		}

		return currentInfo;
	}

	TreeNode* largestBSTSubtree(TreeNode* root) {
		int maxSize = 0;
		TreeNode* largestBST = nullptr;
		findLargestBSTSubtree(root, maxSize, largestBST);
		return largestBST;
	}
};