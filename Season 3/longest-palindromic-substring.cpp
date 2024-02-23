/**
 * @file longest-palindromic-substring.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 5. 最长回文子串
 * @version 0.1
 * @date 2022-07-21
 * @link https://leetcode.cn/problems/longest-palindromic-substring/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>
using namespace std;

/**
 * 动态规划的核心思想是将大问题分解为小问题，并存储小问题的结果来避免重复计算。
 * 创建一个二维数组dp，其中dp[i][j]表示字符串从索引i到j的子串是否是回文串。
 * 初始化单个字符都是回文串，即dp[i][i] = true。
 * 两层循环遍历所有的子串，外层循环遍历子串的长度，内层循环遍历子串的开始位置。
 * 对于每个子串，如果两端的字符相同，并且内部也是回文串（或者子串长度小于3），那么这个子串就是回文串。
 * 在遍历的过程中记录并更新最长回文子串的位置。
 *
 */
class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		if (n < 2) return s;

		vector<vector<bool>> dp(n, vector<bool>(n, false));
		int start = 0, maxLen = 1;

		for (int i = 0; i < n; ++i) {
			dp[i][i] = true;
		}

		for (int L = 2; L <= n; ++L) { // L为子串长度
			for (int i = 0; i < n; ++i) {
				int j = L + i - 1; // 子串结束位置
				if (j >= n) break;
				if (s[i] != s[j]) {
					dp[i][j] = false;
				}
				else {
					if (j - i < 3) {
						dp[i][j] = true;
					}
					else {
						dp[i][j] = dp[i + 1][j - 1];
					}
				}

				if (dp[i][j] && L > maxLen) {
					maxLen = L;
					start = i;
				}
			}
		}

		return s.substr(start, maxLen);
	}
};