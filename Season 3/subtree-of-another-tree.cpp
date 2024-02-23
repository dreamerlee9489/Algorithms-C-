/**
 * @file subtree-of-another-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 572. 另一棵树的子树
 * @version 0.1
 * @date 2022-07-20
 * @link https://leetcode.cn/problems/subtree-of-another-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目要求我们判断一个二叉树是否包含另一个二叉树作为它的子树。解决这个问题有几个关键步骤：
 * 相等的树判断：首先需要定义一个函数来判断两棵树是否完全相同。这个函数可以通过递归的方式，比较两个树的每个对应节点。
 * 递归遍历：使用递归遍历原树root中的每一个节点，将每个节点作为起点，调用上面定义的函数来判断以此节点为根的子树是否与subRoot相同。
 * 递归终止条件：如果root为空，根据subRoot是否为空返回相应的结果；如果root和subRoot的根节点的值不同，则返回false。
 * 时间和空间复杂度：在最坏的情况下，我们可能需要遍历整个树中的每个节点并与subRoot进行比较，时间复杂度为O(m*n)，其中m和n分别是root和subRoot的节点个数。空间复杂度为O(h)，h是树的高度，因为递归调用会使用栈空间。
 *
 */
class Solution {
public:
	bool isSubtree(TreeNode* root, TreeNode* subRoot) {
		if (!root) return !subRoot;
		return isSameTree(root, subRoot) || isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
	}

private:
	bool isSameTree(TreeNode* s, TreeNode* t) {
		if (!s && !t) return true;
		if (!s || !t) return false;
		if (s->val != t->val) return false;
		return isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
	}
};
