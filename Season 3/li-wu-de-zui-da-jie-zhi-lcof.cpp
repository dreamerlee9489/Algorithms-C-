/**
 * @file li-wu-de-zui-da-jie-zhi-lcof.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 剑指 Offer 47. 礼物的最大价值
 * @version 0.1
 * @date 2022-07-20
 * @link https://leetcode.cn/problems/li-wu-de-zui-da-jie-zhi-lcof/
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	int maxValue(vector<vector<int>>& grid) {
		size_t rows = grid.size(), cols = grid[0].size();
		vector<vector<int>> dp = vector<vector<int>>(rows, vector<int>(cols));
		dp[0][0] = grid[0][0];
		for (size_t col = 1; col < cols; ++col)
			dp[0][col] = dp[0][col - 1] + grid[0][col];
		for (size_t row = 1; row < rows; ++row)
			dp[row][0] = dp[row - 1][0] + grid[row][0];
		for (size_t row = 1; row < rows; ++row)
			for (size_t col = 1; col < cols; ++col)
				dp[row][col] = max(dp[row - 1][col], dp[row][col - 1]) + grid[row][col];
		return dp[rows - 1][cols - 1];
	}
};
