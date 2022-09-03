/**
 * @file construct-binary-tree-from-preorder-and-inorder-traversal.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 105. 从前序与中序遍历序列构造二叉树
 * @version 0.1
 * @date 2022-08-08
 * @link
 * https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 * @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  unordered_map<int, int> map;

  TreeNode *myBuildTree(vector<int> &preorder, vector<int> &inorder,
                        int preLeftBound, int preRightBound, int inLeftBound,
                        int inRightBound) {
    if (preLeftBound > preRightBound)
      return nullptr;
    int preRootIdx = preLeftBound;
    int inRootIdx = map[preorder[preRootIdx]];
    int leftSize = inRootIdx - inLeftBound;
    TreeNode *root = new TreeNode(preorder[preRootIdx]);
    root->left = myBuildTree(preorder, inorder, preRootIdx + 1,
                             preRootIdx + leftSize, inLeftBound, inRootIdx - 1);
    root->right = myBuildTree(preorder, inorder, preRootIdx + leftSize + 1,
                              preRightBound, inRootIdx + 1, inRightBound);
    return root;
  }

public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    for (int i = 0; i < inorder.size(); i++)
      map[inorder[i]] = i;
    return myBuildTree(preorder, inorder, 0, preorder.size() - 1, 0,
                       inorder.size() - 1);
  }
};

int main(int argc, char const *argv[]) {
  vector<int> preorder = {3, 9, 20, 15, 7};
  vector<int> inorder = {9, 3, 15, 20, 7};
  TreeNode *root = Solution().buildTree(preorder, inorder);
  return 0;
}
