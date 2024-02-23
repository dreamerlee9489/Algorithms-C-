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
#include <vector>
using namespace std;

/**
 * 为了解决这个问题，我们可以使用动态规划（Dynamic Programming，DP）的方法。动态规划是一种将复杂问题分解为小问题解决的策略，通常用于求解最优化问题。在这个问题中，我们可以定义一个DP数组，其中dp[i][j]代表从左上角（起点）到达位置(i, j)时能拿到的珠宝的最大价值。
 * 解题技巧总结：
 * 初始化DP数组：创建一个与珠宝架相同大小的DP数组，并将左上角的值初始化为frame的左上角的价值。
 * 填充DP数组的第一行和第一列：因为只能向右或向下移动，所以第一行的每个位置的最大价值就是它左边所有珠宝价值的累加，第一列同理。
 * 填充DP数组的其余位置：对于DP数组中的其他位置dp[i][j]，其值应该是其上方(dp[i-1][j])或左方(dp[i][j-1])的最大价值加上当前位置的珠宝价值frame[i][j]。
 * 遍历顺序：从左上角开始，按行或按列遍历整个矩阵。
 * 结果：DP数组的最右下角的值即为结果。
 *
 */
class Solution {
public:
	int jewelleryValue(vector<vector<int>>& frame) {
		int rows = frame.size();
		int cols = frame[0].size();

		// 创建DP数组
		vector<vector<int>> dp(rows, vector<int>(cols, 0));
		dp[0][0] = frame[0][0];

		// 初始化第一行和第一列
		for (int i = 1; i < rows; ++i) {
			dp[i][0] = dp[i - 1][0] + frame[i][0];
		}
		for (int j = 1; j < cols; ++j) {
			dp[0][j] = dp[0][j - 1] + frame[0][j];
		}

		// 填充剩余的DP数组
		for (int i = 1; i < rows; ++i) {
			for (int j = 1; j < cols; ++j) {
				dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + frame[i][j];
			}
		}

		// 返回结果
		return dp[rows - 1][cols - 1];
	}
};