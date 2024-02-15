/**
 * @file valid-anagram.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 242. 有效的字母异位词
 * @version 0.1
 * @date 2022-07-20
 * @link https://leetcode.cn/problems/valid-anagram/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.empty() || t.empty() || s.size() != t.size())
			return false;
		vector<int> counts = vector<int>(26);
		for (size_t i = 0; i < s.size(); ++i)
			counts[s[i] - 'a']++;
		for (size_t i = 0; i < t.size(); ++i) {
			if (--counts[t[i] - 'a'] < 0)
				return false;
		}
		return true;
	}
};