/**
 * @file move-zeroes.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 283. 移动零
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/move-zeroes/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  void moveZeroes(vector<int> &nums) {
    auto iter =
        remove_if(nums.begin(), nums.end(), [](int a) { return a == 0; });
    while (iter != nums.end())
      *iter++ = 0;
  }
};