/**
 * @file validate-stack-sequences.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 946. 验证栈序列
 * @version 0.1
 * @date 2024-02-15
 * @link https://leetcode.cn/problems/validate-stack-sequences/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
	bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
		int i = 0;
		stack<int> stack;
		for (int& num : pushed) {
			stack.push(num);
			while (!stack.empty() && stack.top() == popped[i]) {
				stack.pop();
				++i;
			}
		}
		return stack.empty();
	}
};