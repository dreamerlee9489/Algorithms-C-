/**
 * @file meeting-rooms-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 253. 会议室 II
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode-cn.com/problems/meeting-rooms-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    int minMeetingRooms(vector<vector<int>> &intervals) {
        if (intervals.empty())
            return 0;
        sort(intervals.begin(), intervals.end(),
             [](vector<int> vec1, vector<int> vec2) { return vec1[0] - vec2[0]; });
        priority_queue<int, vector<int>, greater<int>> heap;
        heap.push(intervals[0][1]);
        for (size_t i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= heap.top())
                heap.pop();
            heap.push(intervals[i][1]);
        }
        return heap.size();
    }
};