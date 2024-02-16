/**
 * @file shortest-path-in-binary-matrix.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 1091. 二进制矩阵中的最短路径
 * @version 0.1
 * @date 2024-02-16
 * @link https://leetcode.cn/problems/shortest-path-in-binary-matrix/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
#include <queue>
using namespace std;

class Solution {
	vector<pair<int, int>> dirs = { {0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1} };

public:
	int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
		int n = grid.size();
		if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0) return -1;
		queue<pair<int, int>> q;
		q.push({ 0, 0 });
		grid[0][0] = 1;
		while (!q.empty()) {
			pair<int, int> top = q.front();
			q.pop();
			if (top.first == n - 1 && top.second == n - 1)
				return grid[top.first][top.second];
			for (auto& dir : dirs) {
				int newX = top.first + dir.first;
				int newY = top.second + dir.second;
				if (newX >= 0 && newX < n && newY >= 0 && newY < n && grid[newX][newY] == 0) {
					q.push({ newX, newY });
					grid[newX][newY] = grid[top.first][top.second] + 1;
				}
			}
		}
		return -1;
	}
};