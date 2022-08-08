/**
 * @file find-the-duplicate-number.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 287. 寻找重复数
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/find-the-duplicate-number/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        vector<int> counts = vector<int>(nums.size());
        for (int i = 0; i < nums.size(); i++)
            if (++counts[nums[i]] == 2)
                return nums[i];
    }
};