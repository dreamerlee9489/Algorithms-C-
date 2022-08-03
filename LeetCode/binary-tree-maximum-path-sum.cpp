/**
 * @file binary-tree-maximum-path-sum.cpp
 * @author your name (you@domain.com)
 * @brief 124. 二叉树中的最大路径和
 * @version 0.1
 * @date 2022-08-03
 * @remark https://leetcode.cn/problems/binary-tree-maximum-path-sum/
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <algorithm>
using namespace std;

class Solution
{
    int sum = INT_MIN;

    int getValue(TreeNode *node)
    {
        if(node == nullptr)
            return 0;
        int lvalue = max(getValue(node->left), 0);
        int rvalue = max(getValue(node->right), 0);
        sum = max(node->val + lvalue + rvalue, sum);
        return node->val + max(lvalue, rvalue);
    }

public:
    int maxPathSum(TreeNode *root)
    {
        getValue(root);
        return sum;
    }
};