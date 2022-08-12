/**
 * @file evaluate-reverse-polish-notation.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 150. 逆波兰表达式求值
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/evaluate-reverse-polish-notation/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <string>
#include <list>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        list<string> _list;
        for (int i = 0; i < tokens.size(); i++)
            _list.emplace_back(tokens[i]);
        for (auto iter = _list.begin(); iter != _list.end(); ++iter) {
            if (*iter == "+") {
                int a = stoi(*prev(prev(iter)));
                int b = stoi(*prev(iter));
                *iter = to_string(a + b);
                _list.erase(prev(prev(iter)), iter);
            } else if (*iter == "-") {
                int a = stoi(*prev(prev(iter)));
                int b = stoi(*prev(iter));
                *iter = to_string(a - b);
                _list.erase(prev(prev(iter)), iter);
            } else if (*iter == "*") {
                int a = stoi(*prev(prev(iter)));
                int b = stoi(*prev(iter));
                *iter = to_string(a * b);
                _list.erase(prev(prev(iter)), iter);
            } else if (*iter == "/") {
                int a = stoi(*prev(prev(iter)));
                int b = stoi(*prev(iter));
                *iter = to_string(a / b);
                _list.erase(prev(prev(iter)), iter);
            }
        }
        return stoi(*_list.begin());
    }
};