/**
 * @file longest-increasing-subsequence.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 300. 最长递增子序列
 * @version 0.1
 * @date 2022-08-02
 * @link https://leetcode.cn/problems/longest-increasing-subsequence/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Solution {
public:
  int lengthOfLIS(vector<int> &nums) {
    if (nums.empty())
      return 0;
    vector<int> dp = vector<int>(nums.size(), 1);
    int max = 1;
    for (size_t i = 0; i < dp.size(); i++) {
      for (size_t j = 0; j < i; j++)
        if (nums[j] < nums[i])
          dp[i] = std::max(dp[i], dp[j] + 1);
      max = std::max(dp[i], max);
    }
    return max;
  }
};

int main(int argc, char const *argv[]) {
  vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18, 115, 99, 8, 6, 102, 106};
  cout << Solution().lengthOfLIS(nums);
  return 0;
}
