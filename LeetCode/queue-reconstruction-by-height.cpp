/**
 * @file queue-reconstruction-by-height.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 406. 根据身高重建队列
 * @version 0.1
 * @date 2024-02-14
 * @link https://leetcode.cn/problems/queue-reconstruction-by-height/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b) {
			// 身高降序排列，位置升序排列
			return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]);
			});
		vector<vector<int>> queue;
		for (vector<int>& person : people)
			queue.insert(queue.begin() + person[1], person);
		return queue;
	}
};