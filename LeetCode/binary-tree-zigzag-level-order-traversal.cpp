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
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root != nullptr) {
			list<TreeNode*> lst;
			lst.push_back(root);
			res.push_back({ root->val });
			int lvCnt = 1, h = 1;
			while (!lst.empty()) {
				TreeNode* top = lst.front();
				lst.pop_front();
				if (top->left != nullptr)
					lst.push_back(top->left);
				if (top->right != nullptr)
					lst.push_back(top->right);
				if (--lvCnt == 0) {
					lvCnt = lst.size();
					vector<int> tmp;
					if (++h & 1) {
						for (auto iter = lst.begin(); iter != lst.end(); ++iter)
							tmp.push_back((*iter)->val);
					}
					else {
						for (auto iter = lst.rbegin(); iter != lst.rend(); ++iter)
							tmp.push_back((*iter)->val);
					}
					if (!tmp.empty())
						res.push_back(move(tmp));
				}
			}
		}
		return res;
	}
};

int main(int argc, char const* argv[]) {
	TreeNode* root = new TreeNode(3);

	root->left = new TreeNode(9);
	root->left->left = nullptr;
	root->left->right = nullptr;

	root->right = new TreeNode(20);
	root->right->left = new TreeNode(15);
	root->right->right = new TreeNode(7);

	auto res = Solution().zigzagLevelOrder(root);
	return 0;
}
