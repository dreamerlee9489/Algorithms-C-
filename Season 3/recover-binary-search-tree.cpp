/**
 * @file recover-binary-search-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 99. 恢复二叉搜索树
 * @version 0.1
 * @date 2022-07-22
 * @remark https://leetcode.cn/problems/recover-binary-search-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

class Solution
{
    TreeNode *prev = nullptr, *first = nullptr, *second = nullptr;

    void find(TreeNode *node)
    {
        if (prev != nullptr && prev->val > node->val)
        {
            if (first == nullptr)
                first = prev;
            second = node;
        }
        prev = node;
    }

    void findWrongNodes(TreeNode *root)
    {
        if (root != nullptr)
        {
            findWrongNodes(root->left);
            find(root);
            findWrongNodes(root->right);
        }
    }

public:
    /**
     * @brief Morris遍历
     * @note 时间复杂度O(N), 空间复杂度O(1)
     * @param root 
     */
    void recoverTree(TreeNode *root)
    {
        TreeNode *node = root;
        while (node != nullptr)
        {
            if (node->left != nullptr)
            {
                TreeNode *pred = node->left;
                while (pred->right != nullptr && pred->right != node)
                    pred = pred->right;
                if (pred->right == nullptr)
                {
                    pred->right = node;
                    node = node->left;
                }
                else
                {
                    find(node);
                    pred->right = nullptr;
                    node = node->right;
                }
            }
            else
            {
                find(node);
                node = node->right;
            }
        }
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }

    void recoverTree1(TreeNode *root)
    {
        findWrongNodes(root);
        int temp = first->val;
        first->val = second->val;
        second->val = temp;
    }
};