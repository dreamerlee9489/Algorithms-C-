/**
 * @file min-stack.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 155. 最小栈
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/min-stack/
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class MinStack {
	stack<int> _stk;
	vector<int> _arr;

public:
	MinStack() {}

	void push(int val) {
		_stk.push(val);
		_arr.emplace_back(val);
	}

	void pop() {
		if (!_stk.empty()) {
			auto iter = _arr.begin();
			while (iter != _arr.end()) {
				if (*iter == _stk.top())
					break;
				++iter;
			}
			_arr.erase(iter);
			_stk.pop();
		}
	}

	int top() { return _stk.top(); }

	int getMin() {
		sort(_arr.begin(), _arr.end());
		return *_arr.begin();
	}
};

int main(int argc, char const* argv[]) {
	// MinStack minStack = MinStack();
	// minStack.push(-2);
	// minStack.push(0);
	// minStack.push(-3);
	// cout << minStack.getMin() << "\n"; //返回 -3.
	// minStack.pop();
	// cout << minStack.top() << "\n";    //返回 0.
	// cout << minStack.getMin() << "\n"; //返回 -2.

	MinStack minStack1 = MinStack();
	minStack1.push(-2);
	minStack1.push(0);
	minStack1.push(-1);
	cout << minStack1.getMin() << "\n"; //返回 -2.
	cout << minStack1.top() << "\n";    //返回 -1.
	minStack1.pop();
	cout << minStack1.getMin() << "\n"; //返回 -2.
	return 0;
}
