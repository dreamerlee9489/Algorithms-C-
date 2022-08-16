/**
 * @file divide-two-integers.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 29. 两数相除
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/divide-two-integers/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

class Solution {
  pair<string, string> myDivide(string nume, string deno) {
    long dividend = stol(nume), divisor = stol(deno);
    if (dividend < divisor)
      return pair<string, string>("0", nume);
    if (dividend == divisor)
      return pair<string, string>("1", "0");
    int div = 0;
    while (dividend >= divisor) {
      dividend -= divisor;
      ++div;
    }
    return pair<string, string>(to_string(div), to_string(dividend));
  }

public:
  int divide(int dividend, int divisor) {
    if (dividend == 0 || (dividend > 0 && dividend < divisor) ||
        (dividend < 0 && dividend > divisor))
      return 0;
    string nume = to_string(abs((long)dividend)),
           deno = to_string(abs((long)divisor));
    string curMole = nume.substr(0, deno.size());
    string res = "";
    int index = curMole.size() - 1;
    while (index < nume.size()) {
      auto p = myDivide(curMole, deno);
      res += p.first;
      ++index;
      if (index < nume.size())
        curMole = p.second + nume[index];
    }
    long ans = 0;
    if ((dividend < 0 && divisor > 0) || (dividend > 0 && divisor < 0))
      ans = -1 * stol(res);
    else
      ans = stol(res);
    if (ans < INT_MIN || ans > INT_MAX)
      return INT_MAX;
    return ans;
  }
};

int main(int argc, char const *argv[]) {
  cout << Solution().divide(10, 3) << "\n";
  cout << Solution().divide(12345, 5) << "\n";
  cout << Solution().divide(54321, 5) << "\n";
  cout << Solution().divide(12345, 50) << "\n";
  cout << Solution().divide(54321, 50) << "\n";
  cout << Solution().divide(7, -3) << "\n";
  cout << Solution().divide(12345, -5) << "\n";
  cout << Solution().divide(-12345, 5) << "\n";
  cout << Solution().divide(-12345, -5) << "\n";
  return 0;
}
