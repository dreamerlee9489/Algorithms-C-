/**
 * @file implement-queue-using-stacks.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 232. 用栈实现队列
 * @version 0.1
 * @date 2022-04-05
 * @remark https://leetcode-cn.com/problems/implement-queue-using-stacks/
 * @copyright Copyright (c) 2022
 * 
 */
#include <stack>
using namespace std;

class MyQueue
{
private:
    stack<int> *inStack, *outStack;
    void checkOutStack()
    {
        if (outStack->empty())
        {
            while (!inStack->empty())
            {
                outStack->push(inStack->top());
                inStack->pop();
            }
        }
    }

public:
    MyQueue()
    {
        inStack = new stack<int>();
        outStack = new stack<int>();
    }

    void push(int x)
    {
        inStack->push(x);
    }

    int pop()
    {
        checkOutStack();
        int out = outStack->top();
        outStack->pop();
        return out;
    }

    int peek()
    {
        checkOutStack();
        int out = outStack->top();
        return out;
    }

    bool empty()
    {
        return inStack->empty() && outStack->empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */