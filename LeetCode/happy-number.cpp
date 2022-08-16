/**
 * @file happy-number.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 202. 快乐数
 * @version 0.1
 * @date 2022-08-05
 * @link https://leetcode.cn/problems/happy-number/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <cmath>
#include <iostream>
#include <stack>

using namespace std;

class Solution {
public:
  bool isHappy(int n) {
    stack<int> stk;
    int round = 0;
    while (n != 1) {
      while (n != 0) {
        stk.push(n % 10);
        n /= 10;
      }
      while (!stk.empty()) {
        n += pow(stk.top(), 2);
        stk.pop();
      }
      if (++round > 9)
        return false;
    }
    return true;
  }
};

int main(int argc, char const *argv[]) {
  // cout << Solution().isHappy(19);
  cout << Solution().isHappy(2);
  return 0;
}
