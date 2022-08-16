/**
 * @file sub-sort-lcci.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 面试题 16.16. 部分排序
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/sub-sort-lcci/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> subSort(vector<int> &array) {
    if (array.empty())
      return vector<int>({-1, -1});
    int max = array[0], min = array[array.size() - 1];
    int r = -1, l = -1;
    for (int i = 1; i < array.size(); i++) {
      if (array[i] >= max)
        max = array[i];
      else
        r = i;
    }
    if (r != -1) {
      for (int i = array.size() - 2; i >= 0; i--) {
        if (array[i] <= min)
          min = array[i];
        else
          l = i;
      }
    }
    return vector<int>({l, r});
  }
};