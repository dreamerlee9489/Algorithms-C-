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
#include <stack>
#include <vector>
using namespace std;

class Solution {
  vector<int> res;

  /**
   * @brief Morris遍历
   * @param root 
   */
  void inorder(TreeNode *root) {
    TreeNode *node = root;
    while (node) {
      if (node->left) {
        TreeNode *prev = node->left;
        while (prev->right && prev->right != node) {
          prev = prev->right;
        }
        if (prev->right == node) {
          prev->right = nullptr;
          res.emplace_back(node->val);
          node = node->right;
        } else {
          prev->right = node;
          node = node->left;
        }
      } else {
        res.emplace_back(node->val);
        node = node->right;
      }
    }
  }

  /**
   * @brief 迭代遍历
   * @param root 
   */
  void inorder1(TreeNode *root) {
    stack<TreeNode *> stk;
    TreeNode *node = root;
    while (!stk.empty() || node) {
      while (node) {
        stk.emplace(node);
        node = node->left;
      }
      node = stk.top();
      stk.pop();
      res.emplace_back(node->val);
      node = node->right;
    }
  }

  /**
   * @brief 递归遍历
   * @param root 
   */
  void inorder2(TreeNode *root) {
    if (root != nullptr) {
      inorder2(root->left);
      res.emplace_back(root->val);
      inorder2(root->right);
    }
  }

public:
  vector<int> inorderTraversal(TreeNode *root) {
    inorder(root);
    return res;
  }
};