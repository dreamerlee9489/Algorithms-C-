/**
 * @file coin-change.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 322. 零钱兑换
 * @version 0.1
 * @date 2022-08-02
 * @link https://leetcode.cn/problems/coin-change/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int coinChange(vector<int> &coins, int amount) {
    if (coins.empty() || amount == 0)
      return 0;
    vector<int> dp = vector<int>(amount + 1);
    for (int i = 1; i <= amount; i++) {
      int count = INT_MAX;
      for (int j = 0; j < coins.size(); j++)
        if (i >= coins[j])
          if (dp[i - coins[j]] >= 0 && dp[i - coins[j]] < count)
            count = dp[i - coins[j]];
      dp[i] = count == INT_MAX ? -1 : count + 1;
    }
    return dp[amount];
  }
};

int main(int argc, char const *argv[]) {
  vector<int> nums1 = {186, 419, 83, 408};
  int count = Solution().coinChange(nums1, 6249);
  return 0;
}
