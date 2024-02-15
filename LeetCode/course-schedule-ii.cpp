/**
 * @file course-schedule-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 210. 课程表 II
 * @version 0.1
 * @date 2022-08-13
 * @link https://leetcode.cn/problems/course-schedule-ii/
 * @copyright Copyright (c) 2022
 *
 */
#include <stack>
#include <vector>

using namespace std;

class Solution {
	vector<vector<int>> edges;
	vector<int> visited;
	stack<int> order;
	bool valid = true;

	void dfs(int index) {
		visited[index] = -1;
		for (int i : edges[index]) {
			if (visited[i] == -1) {
				valid = false;
				return;
			}
			else if (visited[i] == 0) {
				dfs(i);
				if (!valid)
					return;
			}
		}
		order.emplace(index);
		visited[index] = 1;
	}

public:
	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
		vector<int> res;
		edges = vector<vector<int>>(numCourses);
		visited = vector<int>(numCourses);
		for (auto& vec : prerequisites)
			edges[vec[1]].emplace_back(vec[0]);
		for (int i = 0; i < numCourses; i++) {
			if (visited[i] == 0)
				dfs(i);
			if (!valid)
				return res;
		}
		while (!order.empty()) {
			res.emplace_back(order.top());
			order.pop();
		}
		return res;
	}
};