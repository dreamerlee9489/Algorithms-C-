/**
 * @file reverse-string.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 344. 反转字符串
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/reverse-string/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
	void reverseString(vector<char>& s) {
		int l = 0, r = s.size() - 1;
		while (l < r) {
			char tmp = s[l];
			s[l++] = s[r];
			s[r--] = tmp;
		}
	}
};