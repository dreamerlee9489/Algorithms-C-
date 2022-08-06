/**
 * @file min-stack.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 155. 最小栈
 * @version 0.1
 * @date 2022-07-19
 * @link https://leetcode.cn/problems/min-stack/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>

using namespace std;

class MinStack {
    struct Node {
        int _val = 0, _min = 0;
        Node *_next = nullptr;

        Node(int val, int min_, Node *next) {
            _val = val;
            _min = min_;
            _next = next;
        }
    };

    Node *head = nullptr;

public:
    MinStack() {
        head = new Node(0, INT_MAX, nullptr);
    }

    void push(int val) {
        head = new Node(val, std::min(val, head->_min), head);
    }

    void pop() {
        head = head->_next;
    }

    int top() {
        return head->_val;
    }

    int getMin() {
        return head->_min;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */