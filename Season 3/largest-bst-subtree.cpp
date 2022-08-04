/**
 * @file largest-bst-subtree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 333. 最大BST子树
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode-cn.com/problems/largest-bst-subtree/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

class Solution
{
    struct Info
    {
        TreeNode *root = nullptr;
        int size = 0, max = 0, min = 0;
        Info(TreeNode *root, int size, int max, int min)
        {
            this->root = root;
            this->size = size;
            this->max = max;
            this->min = min;
        }
    };

    Info *getInfo(TreeNode *root)
    {
        if (root == nullptr)
            return nullptr;
        Info *li = getInfo(root->left);
        Info *ri = getInfo(root->right);
        int leftSize = -1, rightSize = -1, max = root->val, min = root->val;
        if (li == nullptr)
            leftSize = 0;
        else if (li->root == root->left && root->val > li->max)
        {
            leftSize = li->size;
            min = li->min;
        }
        if (ri == nullptr)
            rightSize = 0;
        else if (ri->root == root->right && root->val < ri->min)
        {
            rightSize = ri->size;
            max = ri->max;
        }
        if (leftSize >= 0 && rightSize >= 0)
            return new Info(root, 1 + leftSize + rightSize, max, min);
        if (li != nullptr && ri != nullptr)
            return li->size > ri->size ? li : ri;
        return li != nullptr ? li : ri;
    }

public:
    int largestBSTSubtree(TreeNode *root) { return root == nullptr ? 0 : getInfo(root)->size; }
};