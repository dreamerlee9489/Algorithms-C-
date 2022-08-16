/**
 * @file inorder-successor-in-bst.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 285. 二叉搜索树中的中序后继
 * @version 0.1
 * @date 2022-08-14
 * @link https://leetcode.cn/problems/inorder-successor-in-bst/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <stack>

using namespace std;

class Solution {
public:
  TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p) {
    stack<TreeNode *> _stk;
    TreeNode *prev = nullptr, *curr = root;
    while (curr || !_stk.empty()) {
      while (curr) {
        _stk.emplace(curr);
        curr = curr->left;
      }
      curr = _stk.top();
      _stk.pop();
      if (prev == p)
        return curr;
      prev = curr;
      curr = curr->right;
    }
    return nullptr;
  }
};