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

class Solution {
public:
	int reverse(int x) {
		int res = 0;
		while (x != 0) {
			int prevRes = res;
			int mod = x % 10;
			res = prevRes * 10 + mod;
			if ((res - mod) / 10 != prevRes)
				return 0;
			x /= 10;
		}
		return res;
	}
};