/**
 * @file edit-distance.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 72. 编辑距离
 * @version 0.1
 * @date 2022-07-21
 * @link https://leetcode.cn/problems/edit-distance/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <string>
#include <algorithm> // 为了使用std::min

 /**
  * 为了解决编辑距离问题，我们可以使用动态规划。这个问题的关键是找到一种方法来逐步构建从一个字符串转换到另一个字符串的最小操作次数。我们可以定义一个二维数组dp，其中dp[i][j]表示将word1的前i个字符转换成word2的前j个字符所需要的最少操作数。
  * 解题技巧总结：
  * 初始化一个二维数组dp，大小为(m+1) x (n+1)，其中m和n分别是word1和word2的长度。dp[i][j]的含义是，word1前i个字符转换成word2前j个字符的最小编辑距离。
  * 填充dp数组的第一行和第一列。dp[0][j]表示空字符串转换成word2前j个字符需要的操作数，显然需要j次插入操作；dp[i][0]表示将word1的前i个字符删除成空字符串需要的操作数，显然是i次删除操作。
  * 遍历word1和word2，填充剩余的dp数组。对于每一对字符word1[i]和word2[j]：
  * 	如果它们相同，则dp[i][j] = dp[i-1][j-1]；因为不需要进行任何操作。
  * 	如果它们不同，我们需要考虑三种操作：
  * 		插入一个字符：dp[i][j-1] + 1
  * 		删除一个字符：dp[i-1][j] + 1
  * 		替换一个字符：dp[i-1][j-1] + 1
  * 	我们取这三个操作的最小值作为dp[i][j]。
  * 继续填充dp数组，直到我们计算出dp[m][n]，这就是将word1转换成word2的最少操作数。
  * 返回dp[m][n]作为结果。
  *
  */
class Solution {
public:
	int minDistance(std::string word1, std::string word2) {
		int m = word1.length(), n = word2.length();
		std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

		// 填充第一行和第一列
		for (int i = 1; i <= m; ++i) {
			dp[i][0] = i;
		}
		for (int j = 1; j <= n; ++j) {
			dp[0][j] = j;
		}

		// 填充剩余的dp数组
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (word1[i - 1] == word2[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = std::min({ dp[i - 1][j] + 1,    // 删除
											dp[i][j - 1] + 1,    // 插入
											dp[i - 1][j - 1] + 1 // 替换
						});
				}
			}
		}

		return dp[m][n];
	}
};