/**
 * @file generate-parentheses.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 22. 括号生成
 * @version 0.1
 * @date 2022-08-05
 * @link https://leetcode.cn/problems/generate-parentheses/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
	void dfs(int layer, int lRemain, int rRemain, string str,
		vector<string>& res) {
		if (layer == str.size()) {
			res.emplace_back(str);
			return;
		}
		if (lRemain > 0) {
			str[layer] = '(';
			dfs(layer + 1, lRemain - 1, rRemain, str, res);
		}
		if (rRemain > 0 && lRemain != rRemain) {
			str[layer] = ')';
			dfs(layer + 1, lRemain, rRemain - 1, str, res);
		}
	}

public:
	vector<string> generateParenthesis(int n) {
		vector<string> res;
		dfs(0, n, n, string(n << 1, '0'), res);
		return res;
	}
};

int main(int argc, char const* argv[]) {
	auto res = Solution().generateParenthesis(3);
	return 0;
}
