/**
 * @file power-of-three.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 326. 3 的幂
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/power-of-three/
 * @copyright Copyright (c) 2022
 *
 */
class Solution {
public:
	bool isPowerOfThree(int n) {
		if (n <= 0)
			return false;
		if (n == 1)
			return true;
		while (n > 1) {
			if (n % 3 != 0)
				return false;
			n /= 3;
		}
		return true;
	}
};