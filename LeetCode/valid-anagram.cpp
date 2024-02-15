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
#include <unordered_map>

using namespace std;

class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.size() != t.size())
			return false;
		unordered_map<char, int> _map1, _map2;
		for (char& c : s)
			++_map1[c];
		for (char& c : t)
			++_map2[c];
		for (auto& p : _map1) {
			if (p.second != _map2[p.first])
				return false;
		}
		return true;
	}
};