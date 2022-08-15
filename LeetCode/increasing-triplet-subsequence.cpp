/**
 * @file increasing-triplet-subsequence.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 334. 递增的三元子序列
 * @version 0.1
 * @date 2022-08-14
 * @link https://leetcode.cn/problems/increasing-triplet-subsequence/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool increasingTriplet(vector<int> &nums) {
        vector<int> dp(nums.size(), 1);
        int minIdx = 0, midIdx = 0, maxIdx = 0, maxLen = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[minIdx])
                minIdx = i;
            else if (nums[i] > nums[minIdx]) {
                if (nums[i] < nums[midIdx] || dp[midIdx] == 1) {
                    midIdx = i;
                    ++dp[i];
                } else if (nums[i] > nums[midIdx]) {
                    if (dp[midIdx] > 1)
                        return true;
                }
            }
        }
        return false;
    }
};