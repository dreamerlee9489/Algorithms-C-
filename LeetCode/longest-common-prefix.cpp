/**
 * @file longest-common-prefix.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 14. 最长公共前缀
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/longest-common-prefix/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		int count = 0;
		while (count < strs[0].size()) {
			for (int i = 1; i < strs.size(); i++) {
				if (count >= strs[i - 1].size() || strs[i][count] != strs[i - 1][count])
					return strs[0].substr(0, count);
			}
			++count;
		}
		return strs[0].substr(0, count);
	}
};