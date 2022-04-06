// https://leetcode-cn.com/problems/valid-parentheses/
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
