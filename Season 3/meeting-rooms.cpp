/**
 * @file meeting-rooms.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 252. 会议室
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode.cn/problems/meeting-rooms/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
  bool canAttendMeetings(vector<vector<int>> &intervals) {
    if (intervals.empty())
      return true;
    sort(intervals.begin(), intervals.end(),
         [](vector<int> vec1, vector<int> vec2) { return vec1[0] - vec2[0]; });
    for (size_t i = 0; i < intervals.size(); i++)
      if (intervals[i][0] < intervals[i - 1][1])
        return false;
    return true;
  }
};