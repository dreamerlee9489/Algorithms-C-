/**
 * @file invert-binary-tree.cpp
 * @author your name (you@domain.com)
 * @brief 226. 翻转二叉树
 * @version 0.1
 * @date 2022-08-16
 * @link https://leetcode.cn/problems/invert-binary-tree/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"

class Solution {
  void preorder(TreeNode *node) {
    if (node != nullptr) {
      TreeNode *temp = node->left;
      node->left = node->right;
      node->right = temp;
      preorder(node->left);
      preorder(node->right);
    }
  }

public:
  TreeNode *invertTree(TreeNode *root) {
    preorder(root);
    return root;
  }
};