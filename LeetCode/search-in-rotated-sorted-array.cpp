/**
 * @file search-in-rotated-sorted-array.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 33. 搜索旋转排序数组
 * @version 0.1
 * @date 2022-08-05
 * @link https://leetcode.cn/problems/search-in-rotated-sorted-array/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
  int search1(vector<int> &nums, int target) {
    if (nums.size() == 1)
      return nums[0] == target ? 0 : -1;
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
      int mid = (l + r) / 2;
      if (nums[mid] == target)
        return mid;
      if (nums[0] <= nums[mid]) {
        if (target >= nums[0] && target < nums[mid])
          r = mid - 1;
        else
          l = mid + 1;
      } else {
        if (target > nums[mid] && target <= nums[nums.size() - 1])
          l = mid + 1;
        else
          r = mid - 1;
      }
    }
    return -1;
  }

  int search(vector<int> &nums, int target) {
    if (nums.size() == 1)
      return nums[0] == target ? 0 : -1;
    unordered_map<int, int> _map;
    for (int i = 0; i < nums.size(); i++)
      _map[nums[i]] = i;
    if (_map.find(target) != _map.end())
      return _map[target];
    return -1;
  }
};