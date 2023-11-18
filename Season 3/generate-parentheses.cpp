/**
 * @file generate-parentheses.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 22. 括号生成
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode.cn/problems/generate-parentheses/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
	void dfs(int index, int leftRemain, int rightRemain, string str,
		vector<string>& list) {
		if (index == str.size()) {
			list.emplace_back(str);
			return;
		}
		if (leftRemain > 0) {
			str[index] = '(';
			dfs(index + 1, leftRemain - 1, rightRemain, str, list);
		}
		if (rightRemain > 0 && leftRemain != rightRemain) {
			str[index] = ')';
			dfs(index + 1, leftRemain, rightRemain - 1, str, list);
		}
	}

public:
	vector<string> generateParenthesis(int n) {
		if (n < 0)
			return vector<string>();
		vector<string> list;
		dfs(0, n, n, string(n << 1, '0'), list);
		return list;
	}
};