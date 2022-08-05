/**
 * @file basic-calculator-ii.cpp
 * @author your name (you@domain.com)
 * @brief 227. 基本计算器 II
 * @version 0.1
 * @date 2022-08-05
 * @link https://leetcode.cn/problems/basic-calculator-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
using namespace std;

class Solution
{
    stack<int> nums;
    stack<char> ops;

    int priority(char op)
    {
        switch (op)
        {
        case '+':
        case '-':
            return 0;
        case '*':
        case '/':
            return 1;
        default:
            return -1;
        }
    }

    void calculate()
    {
        char op = ops.top();
        ops.pop();
        int num1 = nums.top();
        nums.pop();
        int num0 = nums.top();
        nums.pop();
        switch (op)
        {
        case '+':
            nums.push(num0 + num1);
            break;
        case '-':
            nums.push(num0 - num1);
            break;
        case '*':
            nums.push(num0 * num1);
            break;
        case '/':
            nums.push(num0 / num1);
            break;
        }
    }

public:
    int calculate(string s)
    {
        s += '$';
        ops.push('$');
        stack<int> temp;
        for (size_t i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
                continue;
            int val = s[i] - '0';
            if (val >= 0 && val <= 9)
                temp.push(val);
            else
            {
                int num = 0, index = 0;
                while (!temp.empty())
                {
                    num += temp.top() * pow(10, index++);
                    temp.pop();
                }
                nums.push(num);
                if (priority(s[i]) > priority(ops.top()))
                    ops.push(s[i]);
                else
                {
                    while (ops.size() > 1 && priority(s[i]) <= priority(ops.top()))
                        calculate();
                    ops.push(s[i]);
                }
            }
        }
        return nums.top();
    }
};

int main(int argc, char const *argv[])
{
    // cout << Solution().calculate("3+2*2") << "\n";
    // cout << Solution().calculate(" 3/2 ") << "\n";
    // cout << Solution().calculate(" 3+5 / 2 ") << "\n";
    cout << Solution().calculate("3+5-6*4+7/2*8-9*2+10") << "\n";
    return 0;
}
