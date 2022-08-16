/**
 * @file symmetric-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 101. 对称二叉树
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/symmetric-tree/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution1 {
  bool levelorder(TreeNode *node) {
    if (node == nullptr)
      return false;
    queue<TreeNode *> q;
    vector<int> nums;
    q.push(node);
    nums.emplace_back(node->val);
    int levelCount = 1;
    while (!q.empty()) {
      TreeNode *top = q.front();
      q.pop();
      auto iter = nums.begin();
      while (iter != nums.end()) {
        if (*iter == top->val)
          break;
        ++iter;
      }
      nums.erase(iter);
      if (top->left != nullptr) {
        q.push(top->left);
        nums.emplace_back(top->left->val);
      }
      if (top->right != nullptr) {
        q.push(top->right);
        nums.emplace_back(top->right->val);
      }
      --levelCount;
      if (levelCount == 0) {
        levelCount = q.size();
        int l = 0, r = nums.size() - 1;
        while (l < r) {
          if (nums[l] != nums[r])
            return false;
          ++l;
          --r;
        }
      }
    }
    return true;
  }

  void inorder(TreeNode *node, vector<int> &nums) {
    if (node != nullptr) {
      inorder(node->left, nums);
      if (node->left == nullptr && node->right != nullptr)
        nums.emplace_back(INT_MIN);
      nums.emplace_back(node->val);
      if (node->left != nullptr && node->right == nullptr)
        nums.emplace_back(INT_MIN);
      inorder(node->right, nums);
    }
  }

public:
  bool isSymmetric(TreeNode *root) {
    vector<int> nums;
    inorder(root, nums);
    int l = 0, r = nums.size() - 1;
    while (l < r) {
      if (nums[l] != nums[r])
        return false;
      ++l;
      --r;
    }
    return levelorder(root);
  }
};

class Solution {
  bool check(TreeNode *left, TreeNode *right) {
    if (left == nullptr && right == nullptr)
      return true;
    if (left == nullptr || right == nullptr)
      return false;
    return (left->val == right->val) && check(left->left, right->right) &&
           check(left->right, right->left);
  }

public:
  bool isSymmetric(TreeNode *root) { return check(root, root); }
};

int main(int argc, char const *argv[]) {
  TreeNode *root1 = new TreeNode(5);
  root1->left = new TreeNode(4);
  root1->left->left = nullptr;
  root1->left->right = new TreeNode(1);
  root1->left->right->left = new TreeNode(2);
  root1->right = new TreeNode(1);
  root1->right->right = new TreeNode(4);
  root1->right->right->left = new TreeNode(2);
  cout << Solution().isSymmetric(root1);

  TreeNode *root2 = new TreeNode(1);
  root2->left = new TreeNode(2);
  root2->left->left = new TreeNode(3);
  root2->left->right = new TreeNode(4);
  root2->right = new TreeNode(2);
  root2->right->left = new TreeNode(4);
  root2->right->right = new TreeNode(3);
  cout << Solution().isSymmetric(root2);
  return 0;
}
