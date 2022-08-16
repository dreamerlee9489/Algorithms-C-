/**
 * @file meeting-rooms-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 253. 会议室 II
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/meeting-rooms-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
  int minMeetingRooms(vector<vector<int>> &intervals) {
    if (intervals.empty())
      return 0;
    sort(intervals.begin(), intervals.end(),
         [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
    priority_queue<int, vector<int>, greater<int>> que;
    que.push(intervals[0][1]);
    for (int i = 1; i < intervals.size(); i++) {
      if (intervals[i][0] >= que.top())
        que.pop();
      que.push(intervals[i][1]);
    }
    return que.size();
  }
};

int main(int argc, char const *argv[]) {
  vector<vector<int>> intervals = {{0, 30}, {5, 10}, {15, 20}};
  cout << Solution().minMeetingRooms(intervals) << "\n";
  return 0;
}
