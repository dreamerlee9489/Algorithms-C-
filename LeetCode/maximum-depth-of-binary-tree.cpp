/**
 * @file maximum-depth-of-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 104. 二叉树的最大深度
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/maximum-depth-of-binary-tree/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include "./TreeNode.hpp"
using namespace std;

class Solution
{
    int height = 0;

    void inorder(int layer, TreeNode *node)
    {
        if(node != nullptr)
        {
            inorder(layer + 1, node->left);
            height = max(layer + 1, height);
            inorder(layer + 1, node->right);
        }
    }

public:
    int maxDepth(TreeNode *root)
    {
        inorder(0, root);
        return height;
    }
};