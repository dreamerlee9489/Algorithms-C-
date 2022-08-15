/**
 * @file kth-smallest-element-in-a-bst.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 230. 二叉搜索树中第K小的元素
 * @version 0.1
 * @date 2022-08-13
 * @link https://leetcode.cn/problems/kth-smallest-element-in-a-bst/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <stack>
#include "./TreeNode.hpp"

using namespace std;

class Solution {
    stack<int> _stack;

    void inorder(TreeNode *node, int k) {
        if (node != nullptr) {
            inorder(node->left, k);
            if (_stack.size() < k)
                _stack.emplace(node->val);
            inorder(node->right, k);
        }
    }

public:
    int kthSmallest(TreeNode *root, int k) {
        inorder(root, k);
        return _stack.top();
    }
};