/**
 * @file min-stack.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 155. 最小栈
 * @version 0.1
 * @date 2022-07-19
 * @link https://leetcode.cn/problems/min-stack/
 * @copyright Copyright (c) 2022
 *
 */
#include <stack>

 /**
  * 解题技巧总结：
  * 为了实现一个最小栈，除了常规的栈操作外，需要在常数时间内检索到最小元素。以下是实现这种数据结构的关键点：
  * 辅助栈：使用一个辅助的栈来存储每个状态下的最小值。每次有新元素入栈时，比较新元素与当前最小值，将较小值压入辅助栈。
  * 同步压栈和出栈：保持辅助栈与主栈的同步操作，即当主栈进行压栈或出栈操作时，辅助栈也要做出相应的操作。
  * 初始化最小值：在辅助栈中预先压入一个最大值，以便在主栈第一次压入元素时能够顺利地将这个元素作为最小值压入辅助栈。
  * 边界条件处理：在进行pop和getMin操作前，确保栈不为空，避免异常。
  *
  */
class MinStack {
	std::stack<int> s;        // 主栈，用于存储所有元素
	std::stack<int> minStack; // 辅助栈，用于存储当前最小元素

public:
	MinStack() {
		// 初始化时可选择不做任何操作
	}

	void push(int val) {
		// 将元素压入主栈
		s.push(val);
		// 如果辅助栈为空，或新元素小于等于辅助栈顶元素，则将新元素压入辅助栈
		if (minStack.empty() || val <= minStack.top()) {
			minStack.push(val);
		}
	}

	void pop() {
		// 如果主栈顶元素等于辅助栈顶元素，同时弹出辅助栈顶元素
		if (!s.empty() && s.top() == minStack.top()) {
			minStack.pop();
		}
		// 弹出主栈顶元素
		s.pop();
	}

	int top() {
		// 返回主栈顶元素
		return s.top();
	}

	int getMin() {
		// 返回辅助栈顶元素，即当前最小元素
		return minStack.top();
	}
};