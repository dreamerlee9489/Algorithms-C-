/**
 * @file binary-tree-zigzag-level-order-traversal.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 103. 二叉树的锯齿形层序遍历
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/
 * @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <list>
#include <vector>

using namespace std;

class Solution {
  void preorder(int layer, TreeNode *node, vector<list<int>> &res) {
    if (node != nullptr) {
      if (layer >= res.size())
        res.emplace(res.begin() + layer, list<int>({node->val}));
      else if ((layer & 1) == 0)
        res[layer].emplace_back(node->val);
      else
        res[layer].emplace_front(node->val);
      preorder(layer + 1, node->left, res);
      preorder(layer + 1, node->right, res);
    }
  }

public:
  vector<vector<int>> zigzagLevelOrder(TreeNode *root) {
    vector<list<int>> resList;
    preorder(0, root, resList);
    vector<vector<int>> resVec(resList.size());
    for (int i = 0; i < resList.size(); i++)
      for (int val : resList[i])
        resVec[i].emplace_back(val);
    return resVec;
  }
};

int main(int argc, char const *argv[]) {
  TreeNode *root = new TreeNode(3);

  root->left = new TreeNode(9);
  root->left->left = nullptr;
  root->left->right = nullptr;

  root->right = new TreeNode(20);
  root->right->left = new TreeNode(15);
  root->right->right = new TreeNode(7);

  auto res = Solution().zigzagLevelOrder(root);
  return 0;
}
