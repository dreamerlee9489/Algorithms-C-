/**
 * @file perfect-squares.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 279. 完全平方数
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/perfect-squares/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  int numSquares(int n) {
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++) {
      int minN = INT_MAX;
      for (int j = 1; j * j <= i; j++)
        minN = min(minN, dp[i - j * j]);
      dp[i] = minN + 1;
    }
    return dp[n];
  }
};