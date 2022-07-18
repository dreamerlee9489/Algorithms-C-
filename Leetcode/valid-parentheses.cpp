/**
 * @file valid-parentheses.cpp
 * @author 354149166@qq.com
 * @brief 20. 有效的括号
 * @version 0.1
 * @date 2022-04-05
 * @note https://leetcode-cn.com/problems/valid-parentheses/
 * @copyright Copyright (c) 2022
 * 
 */
#include <string>
#include <stack>
#include <iostream>
using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> _stack = stack<char>();
        for (size_t i = 0; i < s.size(); ++i)
        {
            char c = s.at(i);
            if (c == '(' || c == '[' || c == '{')
                _stack.push(c);
            else
            {
                if (_stack.empty())
                    return false;
                if (_stack.top() == '(' && c != ')')
                    return false;
                if (_stack.top() == '[' && c != ']')
                    return false;
                if (_stack.top() == '{' && c != '}')
                    return false;
                _stack.pop();
            }
        }
        return _stack.empty();
    }
};
