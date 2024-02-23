/**
 * @file longest-substring-without-repeating-characters.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 3. 无重复字符的最长子串
 * @version 0.1
 * @date 2022-07-20
 * @link https://leetcode.cn/problems/longest-substring-without-repeating-characters/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <unordered_map>
using namespace std;

/**
 * 解决这个问题的一个有效方法是使用滑动窗口技术。滑动窗口可以看作是一个可变大小的窗口，它在字符串上从左到右滑动，用以维护一个没有重复字符的子串。在C++中，可以使用双指针（一个表示窗口的开始，一个表示窗口的结束）和一个哈希表（通常是std::unordered_map或std::unordered_set）来实现这个技术。
 * 解题技巧总结：
 * 初始化：创建两个指针left和right，分别表示滑动窗口的左右边界，初始都指向字符串的开始位置。创建一个哈希表来存储字符和它们最新出现的位置。
 * 扩展窗口：移动right指针来扩展窗口，直到遇到重复字符。
 * 更新哈希表：每次移动right指针时，更新哈希表中对应字符的位置。
 * 收缩窗口：如果遇到重复字符，移动left指针来收缩窗口。通过哈希表判断重复，并更新left指针到重复字符的下一个位置。
 * 更新结果：每次窗口扩展时，更新最长无重复子串的长度。
 * 继续滑动：重复步骤2到5，直到right指针到达字符串的末尾。
 *
 */
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		unordered_map<char, int> charIndexMap;
		int maxLength = 0;
		int left = 0; // 滑动窗口的左边界

		for (int right = 0; right < s.size(); ++right) {
			char currentChar = s[right];

			// 如果字符已经在窗口中，则更新左边界
			if (charIndexMap.find(currentChar) != charIndexMap.end()) {
				// 注意这里使用max函数，因为左边界不能向左移动
				left = max(left, charIndexMap[currentChar] + 1);
			}

			// 更新字符的最新位置，并更新最长子串的长度
			charIndexMap[currentChar] = right;
			maxLength = max(maxLength, right - left + 1);
		}

		return maxLength;
	}
};
