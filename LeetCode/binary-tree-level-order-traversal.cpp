/**
 * @file binary-tree-level-order-traversal.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 102. 二叉树的层序遍历
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/binary-tree-level-order-traversal/
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (!root) return res;
		queue<TreeNode*> q({ root });
		while (!q.empty()) {
			int size = q.size();
			vector<int> currLevel;
			for (int i = 0; i < size; i++) {
				TreeNode* top = q.front();
				q.pop();
				currLevel.push_back(top->val);
				if (top->left)	q.push(top->left);
				if (top->right) q.push(top->right);
			}
			res.push_back(currLevel);
		}
		return res;
	}
};

int main(int argc, char const* argv[]) {
	TreeNode* root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->left->left = new TreeNode(4);
	root->left->right = nullptr;
	root->right = new TreeNode(3);
	root->right->left = nullptr;
	root->right->right = new TreeNode(5);
	auto res = Solution().levelOrder(root);
	return 0;
}
