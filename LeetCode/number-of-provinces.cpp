/**
 * @file number-of-provinces.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 547. 省份数量
 * @version 0.1
 * @date 2024-02-16
 * @link https://leetcode.cn/problems/number-of-provinces/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <vector>
using namespace std;

class Solution {
	int count = 0;
	vector<bool> visited;

	void dfs(vector<vector<int>>& isConnected, int i) {
		visited[i] = true;
		for (int j = 0; j < isConnected.size(); j++) {
			if (isConnected[i][j] == 1 && !visited[j])
				dfs(isConnected, j);
		}
	}

public:
	int findCircleNum(vector<vector<int>>& isConnected) {
		int n = isConnected.size();
		visited = vector<bool>(n, false);
		for (int i = 0; i < n; i++) {
			if (!visited[i]) {
				dfs(isConnected, i);
				++count;
			}
		}
		return count;
	}
};