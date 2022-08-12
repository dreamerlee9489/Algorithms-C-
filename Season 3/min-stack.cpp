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
        int mVal = 0, mMin = 0;
        Node *pNext = nullptr;

        Node(int val, int min, Node *next) {
            mVal = val;
            mMin = min;
            pNext = next;
        }
    };

    Node *head = nullptr;

public:
    MinStack() {
        head = new Node(0, INT_MAX, nullptr);
    }

    void push(int val) {
        head = new Node(val, std::min(val, head->mMin), head);
    }

    void pop() {
        head = head->pNext;
    }

    int top() {
        return head->mVal;
    }

    int getMin() {
        return head->mMin;
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