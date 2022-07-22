/**
 * @file lowest-common-ancestor-of-a-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 236. 二叉树的最近公共祖先
 * @version 0.1
 * @date 2022-07-22
 * @remark https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr || root == p || root == q)
            return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left != nullptr && right != nullptr)
            return root;
        return left != nullptr ? left : right;
    }
};