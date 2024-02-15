/**
 * @file decode-ways.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 91. 解码方法
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/decode-ways/
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	int numDecodings(string s) {
		vector<int> dp(s.size() + 1);
		dp[0] = 1;
		for (int i = 1; i < dp.size(); i++) {
			if (s[i - 1] != '0')
				dp[i] += dp[i - 1];
			if (i > 1 && s[i - 2] != '0' &&
				10 * (s[i - 2] - '0') + (s[i - 1] - '0') <= 26)
				dp[i] += dp[i - 2];
		}
		return dp[s.size()];
	}
};

int main(int argc, char const* argv[]) {
	cout << Solution().numDecodings("2261020112");
	return 0;
}
