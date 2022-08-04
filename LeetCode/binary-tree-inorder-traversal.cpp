/**
 * @file binary-tree-inorder-traversal.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 94. 二叉树的中序遍历
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/binary-tree-inorder-traversal/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <vector>
using namespace std;

class Solution
{
    vector<int> res;
    void inorder(TreeNode* root)
    {
        if(root != nullptr)
        {
            inorderTraversal(root->left);
            res.emplace_back(root->val);
            inorderTraversal(root->right);
        }
    }

public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        inorder(root);
        return res;
    }
};