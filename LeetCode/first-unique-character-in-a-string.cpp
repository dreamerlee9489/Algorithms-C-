/**
 * @file first-unique-character-in-a-string.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 387. 字符串中的第一个唯一字符
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/first-unique-character-in-a-string/
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
	int firstUniqChar(string s) {
		unordered_map<char, int> _map;
		for (int i = 0; i < s.size(); i++)
			++_map[s[i]];
		for (int i = 0; i < s.size(); i++)
			if (_map[s[i]] == 1)
				return i;
		return -1;
	}
};