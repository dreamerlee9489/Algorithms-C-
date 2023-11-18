/**
 * @file valid-parentheses.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 20. 有效的括号
 * @version 0.1
 * @date 2022-08-03
 * @link https://leetcode.cn/problems/valid-parentheses/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
	bool isValid(string s) {
		stack<char> stk;
		for (size_t i = 0; i < s.size(); i++) {
			if (s[i] == '(' || s[i] == '[' || s[i] == '{')
				stk.push(s[i]);
			else {
				if (stk.empty())
					return false;
				switch (s[i]) {
				case ')':
					if (stk.top() == '(')
						stk.pop();
					else
						return false;
					break;
				case ']':
					if (stk.top() == '[')
						stk.pop();
					else
						return false;
					break;
				case '}':
					if (stk.top() == '{')
						stk.pop();
					else
						return false;
					break;
				}
			}
		}
		return stk.empty();
	}
};