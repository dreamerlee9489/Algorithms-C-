/**
 * @file search-a-2d-matrix-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 240. 搜索二维矩阵 II
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/search-a-2d-matrix-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    for (const auto &row : matrix) {
      // 返回指向范围 [first, last) 中首个不小于（即大于或等于） value
      // 的元素的迭代器，或若找不到这种元素则返回 last 。
      const auto iter = lower_bound(row.begin(), row.end(), target);
      if (iter != row.end() && *iter == target)
        return true;
    }
    return false;
  }
};