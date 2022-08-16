/**
 * @file rotate-array.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 189. 轮转数组
 * @version 0.1
 * @date 2022-08-13
 * @link https://leetcode.cn/problems/rotate-array/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <list>
#include <vector>

using namespace std;

class Solution {
public:
  void rotate(vector<int> &nums, int k) {
    list<int> _list1, _list2;
    if (k > nums.size())
      k = k % nums.size();
    for (int i = 0; i < nums.size(); i++) {
      if (i < nums.size() - k)
        _list1.emplace_back(nums[i]);
      else
        _list2.emplace_back(nums[i]);
    }
    _list2.splice(_list2.end(), _list1);
    auto iter = _list2.begin();
    for (int i = 0; i < nums.size(); i++, iter++)
      nums[i] = *iter;
  }
};