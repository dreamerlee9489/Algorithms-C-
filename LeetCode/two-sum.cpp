/**
 * @file two-sum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 1. 两数之和
 * @version 0.1
 * @date 2022-07-27
 * @link https://leetcode.cn/problems/two-sum/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
  // 哈希表增删改查的时间复杂度都是O(1)
  unordered_map<int, int> _map;

public:
  vector<int> twoSum(vector<int> &nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
      auto iter = _map.find(target - nums[i]);
      if (iter != _map.end())
        return vector<int>({iter->second, i});
      _map.emplace(nums[i], i);
    }
    return vector<int>();
  }

  vector<int> twoSum_my(vector<int> &nums, int target) {
    for (int i = 0; i < nums.size(); i++)
      _map.emplace(pair(nums[i], i));
    for (int i = 0; i < nums.size(); i++) {
      auto iter = _map.find(target - nums[i]);
      if (iter != _map.end() && iter->second != i)
        return vector<int>({i, iter->second});
    }
    return vector<int>();
  }
};