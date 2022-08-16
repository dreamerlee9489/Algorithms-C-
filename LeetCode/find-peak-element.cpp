/**
 * @file find-peak-element.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 162. 寻找峰值
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/find-peak-element/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
  int findPeakElement(vector<int> &nums) {
    if (nums.size() == 1)
      return 0;
    if (nums[0] > nums[1])
      return 0;
    if (nums[nums.size() - 1] > nums[nums.size() - 2])
      return nums.size() - 1;
    for (int i = 1; i < nums.size() - 1; i++) {
      int l = i - 1, r = i + 1;
      if (nums[i] > nums[l] && nums[i] > nums[r])
        return i;
    }
    // return 0;
  }
};