/**
 * @file two-sum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 1. 两数之和
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/two-sum/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        if (nums.empty())
            return nums;
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            auto iter = map.find(target - nums[i]);
            if (iter != map.end())
                return vector<int>({iter->second, i});
            map.insert(nums[i], i);
        }
        return vector<int>();
    }
};