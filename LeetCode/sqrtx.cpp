/**
 * @file sqrtx.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 69. x 的平方根
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/sqrtx/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
class Solution {
public:
	int mySqrt(int x) {
		int i = 1;
		while (i * i <= x)
			++i;
		return i - 1;
	}
};