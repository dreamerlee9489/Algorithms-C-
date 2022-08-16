/**
 * @file product-of-array-except-self.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 238. 除自身以外数组的乘积
 * @version 0.1
 * @date 2022-08-13
 * @link https://leetcode.cn/problems/product-of-array-except-self/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <cmath>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> productExceptSelf(vector<int> &nums) {
    vector<int> res(nums.size(), 1);
    unordered_map<int, int> _map;
    for (size_t i = 0; i < nums.size(); i++)
      ++_map[nums[i]];
    for (size_t i = 0; i < nums.size(); i++) {
      --_map[nums[i]];
      if (_map[0] > 0)
        res[i] = 0;
      else {
        for (auto p : _map)
          if (p.first != 1 && p.second != 0)
            res[i] *= pow(p.first, p.second);
      }
      ++_map[nums[i]];
    }
    return res;
  }
};