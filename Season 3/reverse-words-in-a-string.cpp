/**
 * @file reverse-words-in-a-string.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 151. 颠倒字符串中的单词
 * @version 0.1
 * @date 2022-07-20
 * @link https://leetcode.cn/problems/reverse-words-in-a-string/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>

using namespace std;

class Solution {
	void reverse(string& str, int li, int ri) {
		ri--;
		while (li < ri) {
			char temp = str[li];
			str[li] = str[ri];
			str[ri] = temp;
			li++;
			ri--;
		}
	}

public:
	string reverseWords(string str) {
		if (str.empty())
			return str;
		int len = 0, cur = 0;
		bool space = true;
		for (size_t i = 0; i < str.size(); i++) {
			if (str[i] != ' ') {
				str[cur++] = str[i];
				space = false;
			}
			else if (space == false) {
				str[cur++] = ' ';
				space = true;
			}
		}
		len = space ? (cur - 1) : cur;
		if (len <= 0)
			return "";
		reverse(str, 0, len);
		int prevSpaceIdx = -1;
		for (size_t i = 0; i < len; i++) {
			if (str[i] == ' ') {
				reverse(str, prevSpaceIdx + 1, i);
				prevSpaceIdx = i;
			}
		}
		reverse(str, prevSpaceIdx + 1, len);
		return string(str, 0, len);
	}
};