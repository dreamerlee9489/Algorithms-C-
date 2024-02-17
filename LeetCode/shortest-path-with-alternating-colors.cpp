/**
 * @file shortest-path-with-alternating-colors.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 1129. 颜色交替的最短路径
 * @version 0.1
 * @date 2024-02-17
 * @link https://leetcode.cn/problems/shortest-path-with-alternating-colors/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
	vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
		vector<vector<int>> redAdj(n), blueAdj(n);
		for (auto& edge : redEdges)
			redAdj[edge[0]].push_back(edge[1]);
		for (auto& edge : blueEdges)
			blueAdj[edge[0]].push_back(edge[1]);
		queue<pair<int, int>> q;
		vector<vector<bool>> visited(n, vector<bool>(2, false));
		vector<int> answer(n, -1);
		q.push({ 0, 0 });
		q.push({ 0, 1 });
		visited[0][0] = true;
		visited[0][1] = true;
		answer[0] = 0;
		int step = 0;
		while (!q.empty()) {
			int size = q.size();
			while (size--) {
				auto [node, color] = q.front();	//auto& [node, color] = q.front(); 报错
				q.pop();
				auto& adj = (color == 0) ? blueAdj : redAdj;
				int nextColor = 1 - color;
				for (int nextNode : adj[node]) {
					if (!visited[nextNode][nextColor]) {
						visited[nextNode][nextColor] = true;
						q.push({ nextNode, nextColor });
						if (answer[nextNode] == -1) answer[nextNode] = step + 1;
					}
				}
			}
			++step;
		}
		return answer;
	}
};