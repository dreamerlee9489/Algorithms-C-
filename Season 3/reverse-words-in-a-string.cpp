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
#include <algorithm>
#include <string>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目的关键是要反转字符串中的单词顺序，同时删除多余的空格。以下是几个解决这个问题的关键步骤和技巧：
 * 去除首尾和中间多余空格：首先，我们需要消除字符串前后的空格，并将字符串中间的多余空格（即连续的空格）压缩成一个空格。这一步可以通过遍历字符串并构建一个新的字符串、使用标准库的函数，或者先分割后合并的方式实现。
 * 反转整个字符串：去除多余空格后，反转整个字符串。这一步可以通过双指针方法来交换字符，或者使用标准库的reverse函数。
 * 反转每个单词：整个字符串反转后，单词的顺序已经正确了，但是单词内部的字母顺序是反的。因此，我们需要再次遍历反转后的字符串，找到每个单词的开始和结束位置，然后反转单词内部的字符。
 * 时间和空间复杂度：时间复杂度为O(n)，其中n是字符串的长度，因为我们需要遍历整个字符串几次（去空格、反转整个字符串、反转每个单词）。空间复杂度一般为O(n)，因为我们可能需要额外的空间来存储处理后的字符串。
 *
 */
class Solution {
public:
	string reverseWords(string s) {
		// 移除多余空格并反转整个字符串
		trimSpaces(s);
		reverse(s.begin(), s.end());

		// 反转每一个单词
		reverseEachWord(s);

		return s;
	}

private:
	// 辅助函数，用于去除字符串两端的空格以及中间多余的空格
	void trimSpaces(string& s) {
		int n = s.length();
		int left = 0, right = n - 1;
		// 去除两端空格
		while (left <= right && s[left] == ' ') left++;
		while (right >= left && s[right] == ' ') right--;

		// 压缩中间多余空格
		string buffer;
		while (left <= right) {
			if (s[left] != ' ' || buffer.back() != ' ') {
				buffer.push_back(s[left]);
			}
			left++;
		}

		s.swap(buffer); // C++11 以上可以使用
	}

	// 辅助函数，用于反转每一个单词
	void reverseEachWord(string& s) {
		int n = s.length();
		int start = 0, end = 0;
		while (start < n) {
			// 查找单词的末尾
			while (end < n && s[end] != ' ') end++;
			// 反转单词
			reverse(s.begin() + start, s.begin() + end);
			// 更新start，去找下一个单词的开头
			start = end + 1;
			end++;
		}
	}
};