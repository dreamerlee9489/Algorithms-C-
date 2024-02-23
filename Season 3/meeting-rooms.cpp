/**
 * @file meeting-rooms.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 252. 会议室
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode.cn/problems/meeting-rooms/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 解题技巧总结：
 * 排序：首先按照会议的开始时间对会议进行排序。这样可以按时间顺序检查每个会议。
 * 相邻比较：排序后，只需要比较相邻的会议时间。检查一个会议的结束时间是否大于下一个会议的开始时间。
 * 判断冲突：如果存在至少一对相邻会议时间冲突（即前一个会议的结束时间大于下一个会议的开始时间），则该人无法参加所有会议。
 * 返回结果：如果没有任何冲突，返回true；否则，返回false。
 *
 */
class Solution {
public:
	bool canAttendMeetings(vector<vector<int>>& intervals) {
		// 按会议开始时间排序
		sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
			return a[0] < b[0];
			});

		// 遍历会议，检查是否有冲突
		for (int i = 1; i < intervals.size(); ++i) {
			// 如果当前会议的开始时间小于前一个会议的结束时间，则有冲突
			if (intervals[i][0] < intervals[i - 1][1]) {
				return false;
			}
		}

		// 没有冲突，可以参加所有会议
		return true;
	}
};