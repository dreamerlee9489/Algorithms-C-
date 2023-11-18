/**
 * @file edit-distance.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 72. 编辑距离
 * @version 0.1
 * @date 2022-07-21
 * @link https://leetcode.cn/problems/edit-distance/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int minDistance(string word1, string word2) {
		if (word1.empty() && word2.empty())
			return 0;
		vector<vector<int>> dp =
			vector<vector<int>>(word1.size() + 1, vector<int>(word2.size() + 1));
		for (size_t i = 1; i <= word1.size(); i++)
			dp[i][0] = i;
		for (size_t j = 1; j <= word2.size(); j++)
			dp[0][j] = j;
		for (size_t i = 1; i <= word1.size(); i++) {
			for (size_t j = 1; j <= word2.size(); j++) {
				int top = dp[i - 1][j] + 1;
				int left = dp[i][j - 1] + 1;
				int leftTop = dp[i - 1][j - 1];
				if (word1[i - 1] != word2[j - 1])
					leftTop++;
				dp[i][j] = min(min(top, left), leftTop);
			}
		}
		return dp[word1.size()][word2.size()];
	}
};