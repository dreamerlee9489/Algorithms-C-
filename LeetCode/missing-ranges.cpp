/**
 * @file missing-ranges.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 163. 缺失的区间
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/missing-ranges/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  vector<string> findMissingRanges(vector<int> &nums, int lower, int upper) {
    vector<string> res;
    if (nums.size() == 0) {
      if (lower == upper) {
        res.emplace_back(to_string(lower));
      } else {
        res.emplace_back(to_string(lower) + "->" + to_string(upper));
      }
    } else {
      for (int i = 0; i < nums.size(); i++) {
        if (i == 0) {
          int size = nums[i] - lower;
          if (size == 1) {
            res.emplace_back(to_string(lower));
          } else if (size > 1) {
            res.emplace_back(to_string(lower) + "->" + to_string(nums[i] - 1));
          }
        }
        if (i == nums.size() - 1) {
          int size = upper - nums[i];
          if (size == 1) {
            res.emplace_back(to_string(upper));
          } else if (size > 1) {
            res.emplace_back(to_string(nums[i] + 1) + "->" + to_string(upper));
          }
        } else {
          int size = nums[i + 1] - nums[i];
          if (size == 2) {
            res.emplace_back(to_string(nums[i] + 1));
          } else if (size > 2) {
            res.emplace_back(to_string(nums[i] + 1) + "->" +
                             to_string(nums[i + 1] - 1));
          }
        }
      }
    }
    return res;
  }
};