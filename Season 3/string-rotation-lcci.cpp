/**
 * @file string-rotation-lcci.cpp
 * @author
 * @brief 面试题 01.09. 字符串轮转
 * @version 0.1
 * @date 2022-07-20
 * @link https://leetcode.cn/problems/string-rotation-lcci/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目涉及到字符串的旋转问题。检查一个字符串是否是另一个字符串旋转而成可以通过以下步骤进行：
 * 检查长度：如果s1和s2的长度不同，那么s2不可能是s1的旋转字符串，可以直接返回false。
 * 连接字符串：将s1与自身连接，生成一个新的字符串s1s1。
 * 子字符串检查：检查s2是否是s1s1的子字符串。如果是，则s2是s1的旋转字符串；如果不是，则不是。
 * 使用库函数：在C++中，可以使用std::string的find方法来检查一个字符串是否是另一个字符串的子字符串。
 * 时间和空间复杂度：时间复杂度取决于子字符串查找操作，通常为O(n)，n是字符串s1的长度。空间复杂度为O(n)，因为我们创建了一个新的字符串s1s1。
 *
 */
class Solution {
public:
	bool isFlipedString(string s1, string s2) {
		if (s1.length() != s2.length()) return false;
		string s1s1 = s1 + s1;
		return s1s1.find(s2) != string::npos;
	}
};