/**
 * @file word-break.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 139. 单词拆分
 * @version 0.1
 * @date 2022-08-08
 * @link https://leetcode.cn/problems/word-break/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
	unordered_set<string> set;

public:
	bool wordBreak(string s, vector<string>& wordDict) {
		for (string str : wordDict)
			set.emplace(str);
		vector<bool> dp(s.size() + 1, false);
		dp[0] = true;
		for (int i = 1; i < dp.size(); i++) {
			for (int j = 0; j < i; j++) {
				if (dp[j] && (set.find(s.substr(j, i - j)) != set.end())) {
					dp[i] = true;
					break;
				}
			}
		}
		return dp[s.size()];
	}
};