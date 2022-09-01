/**
 * @file basic-calculator-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 227. 基本计算器 II
 * @version 0.1
 * @date 2022-08-05
 * @link https://leetcode.cn/problems/basic-calculator-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Solution {
  stack<int> nums;  // 运算数栈
  stack<char> ops;  // 运算符栈

  /**
   * @brief 定义运算符优先级
   * @param op
   * @return int
   */
  int priority(char op) {
    switch (op) {
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

  /**
   * @brief 弹出两个运算数和一个运算符，并将结果压入运算数栈中
   */
  void calculate() {
    char op = ops.top();
    ops.pop();
    int num1 = nums.top();
    nums.pop();
    int num0 = nums.top();
    nums.pop();
    switch (op) {
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
  int calculate(string s) {
    s += '$';
    ops.push('$');
    s.erase(remove_if(s.begin(), s.end(), [](char ch) { return isspace(ch); }),
            s.end());
    string operand; // 存放一个运算数
    for (size_t i = 0; i < s.size(); i++) {
      int val = s[i] - '0';
      if (val >= 0 && val <= 9)
        operand += s[i];
      else {
        int num = stoi(operand);
        operand.clear();
        nums.push(num);
        // 当前运算符优先级大于栈顶元素,入栈
        if (priority(s[i]) > priority(ops.top()))
          ops.push(s[i]);
        else {  
          // 弹出全部运算符
          while (ops.size() > 1 && priority(s[i]) <= priority(ops.top()))
            calculate();
          ops.push(s[i]);
        }
      }
    }
    return nums.top();
  }
};

int main(int argc, char const *argv[]) {
  cout << Solution().calculate("3+2*2") << "\n";
  cout << Solution().calculate(" 3/2 ") << "\n";
  cout << Solution().calculate(" 3+5 / 2 ") << "\n";
  cout << Solution().calculate("3+5-6*4+7/2*8-9*2+10") << "\n";
  return 0;
}
