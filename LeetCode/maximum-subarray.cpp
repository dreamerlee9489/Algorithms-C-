/**
 * @file maximum-subarray.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 53. 最大子数组和
 * @version 0.1
 * @date 2022-07-31
 * @link https://leetcode.cn/problems/maximum-subarray/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxSubArray(vector<int> &nums) {
    vector<int> dp(nums);
    int maxSum = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      dp[i] = max(dp[i - 1] + nums[i], nums[i]);
      maxSum = max(maxSum, dp[i]);
    }
    return maxSum;
  }
};

int main(int argc, char const *argv[]) {
  vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  cout << Solution().maxSubArray(nums1) << endl;
  vector<int> nums2 = {5, 4, -1, 7, 8};
  cout << Solution().maxSubArray(nums2) << endl;
  vector<int> nums3 = {-2, -1, -2, -10, 0, -5};
  cout << Solution().maxSubArray(nums3) << endl;
  vector<int> nums4 = {1};
  cout << Solution().maxSubArray(nums4) << endl;
  return 0;
}
