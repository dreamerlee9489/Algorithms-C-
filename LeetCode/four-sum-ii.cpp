/**
 * @file four-sum-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 454. 四数相加 II
 * @version 0.1
 * @date 2022-08-08
 * @link https://leetcode.cn/problems/4sum-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3,
                   vector<int> &nums4) {
    unordered_map<int, int> map;
    for (int a : nums1)
      for (int b : nums2)
        ++map[a + b];
    int res = 0;
    for (int c : nums3)
      for (int d : nums4)
        if (map.find(-c - d) != map.end())
          res += map[-c - d];
    return res;
  }
};