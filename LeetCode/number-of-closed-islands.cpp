/**
 * @file number-of-closed-islands.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 1254. 统计封闭岛屿的数目
 * @version 0.1
 * @date 2024-02-16
 * @link https://leetcode.cn/problems/number-of-closed-islands/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
using namespace std;

class Solution {
	int row = 0, col = 0, islands = 0;

	void dfs(vector<vector<int>>& grid, int x, int y) {
		if (x < 0 || x >= row || y < 0 || y >= col || grid[x][y] == 1)
			return;
		grid[x][y] = 1;
		dfs(grid, x - 1, y);
		dfs(grid, x + 1, y);
		dfs(grid, x, y - 1);
		dfs(grid, x, y + 1);
	}

public:
	int closedIsland(vector<vector<int>>& grid) {
		row = grid.size(), col = grid[0].size();
		for (int r = 0; r < row; r++) {
			dfs(grid, r, 0);
			dfs(grid, r, col - 1);
		}
		for (int c = 0; c < col; c++) {
			dfs(grid, 0, c);
			dfs(grid, row - 1, c);
		}
		for (int r = 1; r < row - 1; r++) {
			for (int c = 1; c < col - 1; c++) {
				if (grid[r][c] == 0) {
					++islands;
					dfs(grid, r, c);
				}
			}
		}
		return islands;
	}
};