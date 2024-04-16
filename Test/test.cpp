#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left, * right;
	TreeNode(int val, TreeNode* left = nullptr, TreeNode* right = nullptr) {
		this->val = val;
		this->left = left;
		this->right = right;
	}
};

bool isSameTree(TreeNode* root1, TreeNode* root2) {
	if (!root1 && !root2)	return true;
	if (!root1 || !root2)	return false;
	if (root1->val != root2->val)	return false;
	return isSameTree(root1->left, root2->left) && isSameTree(root1->right, root2->right);
}

void dfs(vector<string>& result, string current, int n, int left, int right) {
	if (current.size() == 2 * n) {
		result.push_back(current);
		return;
	}

	if (left < n) {
		dfs(result, current + '(', n, left + 1, right);
	}

	if (right < left) {
		dfs(result, current + ')', n, left, right + 1);
	}
}

vector<string> test(int n) {
	vector<string> result;
	string current;
	dfs(result, current, n, 0, 0);
	return result;
}

int main(int argc, char const* argv[])
{
	vector<string> res = test(3);
	return 0;
}
