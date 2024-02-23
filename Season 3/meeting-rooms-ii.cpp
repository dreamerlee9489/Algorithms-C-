/**
 * @file meeting-rooms-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 253. 会议室 II
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode-cn.com/problems/meeting-rooms-ii/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/**
 * 解题技巧总结：
 * 排序：首先按照会议的开始时间对会议进行排序。
 * 使用最小堆：使用一个最小堆来跟踪当前进行中的会议的结束时间。最小堆允许我们快速检查最早结束的会议。
 * 遍历会议：按排序后的顺序遍历会议，对于每个会议：
 * 	如果堆不为空且堆顶会议（最早结束的会议）的结束时间小于或等于当前会议的开始时间，那么我们可以在同一个会议室中安排这两个会议。因此，我们可以从堆中移除已结束的会议。
 * 	将当前会议的结束时间添加到堆中。
 * 堆的大小：遍历完成后，堆的大小将表示我们需要的会议室数量，因为堆中存储了所有重叠的会议。
 * 堆优化：在C++中，可以使用priority_queue来实现最小堆。如果考虑到性能，可以在会议开始时间排序后，使用一个变量记录当前的会议室数量，以及一个有序的数据结构（如multiset）来跟踪会议的结束时间。
 *
 */
class Solution {
public:
	int minMeetingRooms(vector<vector<int>>& intervals) {
		if (intervals.empty()) return 0;

		// 按会议开始时间排序
		sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
			return a[0] < b[0];
			});

		// 使用优先队列（最小堆）来跟踪进行中的会议的结束时间
		priority_queue<int, vector<int>, greater<int>> minHeap;

		// 将第一个会议的结束时间加入到堆中
		minHeap.push(intervals[0][1]);

		// 遍历剩余会议
		for (int i = 1; i < intervals.size(); ++i) {
			// 如果当前会议的开始时间大于或等于堆顶的结束时间，弹出堆顶（会议室释放）
			if (intervals[i][0] >= minHeap.top()) {
				minHeap.pop();
			}
			// 将当前会议的结束时间加入堆中
			minHeap.push(intervals[i][1]);
		}

		// 堆的大小即为所需的会议室数量
		return minHeap.size();
	}
};