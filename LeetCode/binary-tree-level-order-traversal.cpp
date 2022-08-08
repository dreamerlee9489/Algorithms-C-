/**
 * @file binary-tree-level-order-traversal.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 102. 二叉树的层序遍历
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/binary-tree-level-order-traversal/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>
#include "./TreeNode.hpp"

using namespace std;

class Solution {
    void preorder(int layer, TreeNode *root, vector<vector<int>> &res) {
        if (root != nullptr) {
            if (layer >= res.size())
                res.emplace(res.begin() + layer, vector<int>({root->val}));
            else
                res[layer].emplace_back(root->val);
            preorder(layer + 1, root->left, res);
            preorder(layer + 1, root->right, res);
        }
    }

public:
    vector<vector<int>> levelOrder(TreeNode *root) {
        vector<vector<int>> res;
        preorder(0, root, res);
        return res;
    }
};

int main(int argc, char const *argv[]) {
    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->left->left = new TreeNode(4);
    root->left->right = nullptr;

    root->right = new TreeNode(3);
    root->right->left = nullptr;
    root->right->right = new TreeNode(5);
    auto res = Solution().levelOrder(root);
    return 0;
}
