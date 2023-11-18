/**
 * @file binary-tree-level-order-traversal.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 102. 二叉树的层序遍历
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/binary-tree-level-order-traversal/
 * @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./TreeNode.hpp"
#include <iostream>
#include <list>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root != nullptr) {
			list<TreeNode*> que;
			que.push_back(root);
			res.push_back({ root->val });
			int lvCnt = 1;
			while (!que.empty()) {
				TreeNode* top = que.front();
				que.pop_front();
				if (top->left != nullptr)
					que.push_back(top->left);
				if (top->right != nullptr)
					que.push_back(top->right);
				if (--lvCnt == 0) {
					vector<int> tmp;
					for (auto node : que)
						tmp.push_back(node->val);
					if (!tmp.empty())
						res.push_back(move(tmp));
					lvCnt = que.size();
				}
			}
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
