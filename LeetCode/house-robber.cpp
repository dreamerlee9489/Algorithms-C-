/**
 * @file house-robber.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 198. 打家劫舍
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/house-robber/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rob(vector<int> &nums) {
        if (nums.size() == 1)
            return nums[0];
        vector<int> dp(nums.size());
        dp[0] = nums[0], dp[1] = nums[1];
        for (int i = 2; i < dp.size(); i++) {
            int max = nums[i];
            for (int j = 0; j < i - 1; j++)
                max = std::max(dp[j] + nums[i], max);
            dp[i] = max;
        }
        return *max_element(dp.begin(), dp.end());
    }
};