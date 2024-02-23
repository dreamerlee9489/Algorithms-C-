/**
 * @file reverse-integer.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 7. 整数反转
 * @version 0.1
 * @date 2022-07-25
 * @link https://leetcode.cn/problems/reverse-integer/
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题的关键在于如何在不使用64位整数的情况下，对一个32位有符号整数进行反转，同时避免反转过程中的整数溢出。这里有几个关键的步骤和策略：
 * 处理正负号：首先判断整数x的正负，可以通过对x求符号来实现。整数反转的过程中，正负号是不会改变的。
 * 逐位反转：去掉整数的符号后，我们可以逐个取出整数的最后一位，然后将其添加到结果的末尾。这可以通过取模和除法操作来实现。
 * 防止溢出：在每次将一个新的数字添加到结果中时，我们需要检查是否会导致溢出。因为环境不允许存储64位整数，所以我们不能直接反转整个数来判断是否溢出。相反，我们可以在添加新的数字之前，检查结果是否大于INT_MAX / 10或小于INT_MIN / 10，因为这将是反转后整数可能溢出的边界。
 * 返回结果：最后，加上正负号后返回反转后的结果。
 * 时间和空间复杂度：时间复杂度为O(log(x))，因为我们每次操作都会将输入值x除以10，所以操作的次数是x数字位数的对数。空间复杂度为O(1)，因为我们只需要有限的几个变量来处理问题。
 *
 */
class Solution {
public:
	int reverse(int x) {
		int reversed = 0;
		while (x != 0) {
			// 取出x的最后一位数字
			int pop = x % 10;
			x /= 10;

			// 检查是否溢出
			if (reversed > INT_MAX / 10 || (reversed == INT_MAX / 10 && pop > 7)) return 0;
			if (reversed < INT_MIN / 10 || (reversed == INT_MIN / 10 && pop < -8)) return 0;

			// 将数字添加到反转后的数中
			reversed = reversed * 10 + pop;
		}
		return reversed;
	}
};