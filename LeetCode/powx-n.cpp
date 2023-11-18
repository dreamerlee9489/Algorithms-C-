/**
 * @file powx-n.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 50. Pow(x, n)
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/powx-n/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
class Solution {
public:
	double myPow(double x, int n) {
		if (n == 0)
			return 1;
		if (n == 1)
			return x;
		if (n == -1)
			return 1 / x;
		double half = myPow(x, n >> 1);
		return n & 1 ? half * half * x : half * half;
	}
};