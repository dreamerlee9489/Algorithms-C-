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

/**
 * 解题技巧总结：
 * 判断两个字符串是否互为字母异位词，本质上是判断两个字符串中每个字符出现的次数是否完全相同。以下是几种常见的方法：
 * 排序方法：对两个字符串分别进行排序，如果它们互为字母异位词，排序后的字符串应该是相同的。然后比较排序后的两个字符串是否相等即可。时间复杂度为O(nlogn)，因为排序操作通常需要O(nlogn)时间。
 * 计数方法：使用一个计数器（通常是一个频率数组或哈希表）来记录每个字符出现的次数。由于字母异位词具有相同的字符频率分布，我们可以通过比较两个字符串中每个字符的频率来判断它们是否互为字母异位词。时间复杂度为O(n)。
 * 
 */
class Solution {
public:
	bool isAnagram(string s, string t) {
		if (s.length() != t.length()) {
			return false;
		}

		vector<int> counts(26, 0); // 因为题目只涉及到字母，所以可以使用长度为26的数组

		for (int i = 0; i < s.length(); ++i) {
			counts[s[i] - 'a']++; // 对字符串 s 中的每个字符计数
			counts[t[i] - 'a']--; // 对字符串 t 中的每个字符计数
		}

		// 如果两个字符串互为字母异位词，那么计数数组中的所有元素都应该是0
		for (int count : counts) {
			if (count != 0) {
				return false;
			}
		}

		return true;
	}
};