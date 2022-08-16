/**
 * @file invert-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 226. 翻转二叉树
 * @version 0.1
 * @date 2022-04-05
 * @link https://leetcode-cn.com/problems/invert-binary-tree/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

class Solution {
public:
  TreeNode *invertTree(TreeNode *root) {
    if (root != nullptr) {
      invertTree(root->left);
      invertTree(root->right);
      TreeNode *temp = root->left;
      root->left = root->right;
      root->right = temp;
    }
    return root;
  }
};