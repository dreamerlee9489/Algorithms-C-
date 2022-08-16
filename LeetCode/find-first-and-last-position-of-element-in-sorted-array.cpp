/**
 * @file find-first-and-last-position-of-element-in-sorted-array.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 34. 在排序数组中查找元素的第一个和最后一个位置
 * @version 0.1
 * @date 2022-08-12
 * @link
 * https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
 * @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> searchRange(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    int index = -1;
    while (left <= right) {
      int mid = (left + right) / 2;
      if (nums[mid] < target) {
        left = mid + 1;
      } else if (nums[mid] > target) {
        right = mid - 1;
      } else {
        index = mid;
        break;
      }
    }
    if (index != -1) {
      int start = index, end = index;
      while (start >= 0) {
        if (nums[start] != nums[index])
          break;
        --start;
      }
      while (end < nums.size()) {
        if (nums[end] != nums[index])
          break;
        ++end;
      }
      return vector<int>({start + 1, end - 1});
    }
    return vector<int>({-1, -1});
  }
};