/**
 * @file lowest-common-ancestor-of-a-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 236. 二叉树的最近公共祖先
 * @version 0.1
 * @date 2022-07-22
 * @link https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

 /**
  * 解决这个问题的一个有效递归方法是后序遍历二叉树。我们可以通过递归来寻找最近公共祖先（LCA），基于以下几点：
  * 递归定义：定义一个递归函数，该函数返回给定子树中存在的p或q的节点。如果p和q都存在，则返回它们的最近公共祖先。
  * 终止条件：如果当前节点为空或等于p或q，则返回当前节点。
  * 递归查找：递归地在左右子树中查找p和q。
  * 后序位置决策：根据左右子树的递归结果决定当前节点的返回值：
  * 	如果左右子树递归结果都非空，说明当前节点就是p和q的最近公共祖先。
  * 	如果只有一个非空，说明p和q都在这一侧，返回非空的子树递归结果。
  * 	如果两侧都为空，返回空。
  * 返回结果：递归回到根节点时，返回的节点即是最近公共祖先。
  *
  */
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// 如果到达叶节点的下一层，或找到p或q，则回溯
		if (root == nullptr || root == p || root == q) return root;

		// 在左右子树中分别寻找p和q
		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);

		// 如果左右子树递归结果都非空，说明p和q分别位于两侧，当前root为最近公共祖先
		if (left != nullptr && right != nullptr) return root;

		// 如果左右子树有一侧为空，则返回非空的那一侧
		return left != nullptr ? left : right;
	}
};