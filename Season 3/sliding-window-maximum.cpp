/**
 * @file sliding-window-maximum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 239. 滑动窗口最大值
 * @version 0.1
 * @date 2022-07-19
 * @link https://leetcode.cn/problems/sliding-window-maximum/
 * @copyright Copyright (c) 2022
 *
 */
#include <deque>
#include <vector>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目要求计算所有滑动窗口的最大值，是一道典型的使用双端队列(deque)解决的问题。以下是解决这个问题的关键步骤和技巧：
 * 使用双端队列：使用一个双端队列来存储当前窗口中的最大值的索引。这个双端队列应该是一个递减队列，即队列的头部是当前窗口的最大值的索引。
 * 维护双端队列：当滑动窗口向右移动时，需要做两件事情来维护队列：
 * 如果队列头部的元素索引已经不在滑动窗口内（即小于当前索引-窗口大小），则从队列头部移除。
 * 从队列尾部开始，移除所有小于当前元素值的索引，因为它们不再可能成为窗口的最大值。
 * 窗口填满前的处理：滑动窗口未完全填满之前，只需添加元素到双端队列而不需要移除。
 * 添加窗口最大值：只有当滑动窗口完全填满后（即索引>=k-1），每次移动时，将队列头部的元素（当前窗口的最大值）添加到结果数组中。
 * 时间和空间复杂度：时间复杂度为O(n)，其中n是数组的长度，每个元素最多进出双端队列一次。空间复杂度为O(k)，双端队列的大小不会超过滑动窗口的大小k。
 *
 */
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> result;
		deque<int> window; // 存储索引

		for (int i = 0; i < nums.size(); ++i) {
			// 移除不在滑动窗口内的元素的索引
			while (!window.empty() && window.front() < i - k + 1) {
				window.pop_front();
			}

			// 移除所有小于当前元素值的索引
			while (!window.empty() && nums[i] > nums[window.back()]) {
				window.pop_back();
			}

			// 将当前元素索引添加到双端队列中
			window.push_back(i);

			// 当窗口长度达到k时，记录当前窗口的最大值
			if (i >= k - 1) {
				result.push_back(nums[window.front()]);
			}
		}

		return result;
	}
};
