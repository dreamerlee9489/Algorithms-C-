/**
 * @file reverse-bits.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 190. 颠倒二进制位
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/reverse-bits/
 * @copyright Copyright (c) 2022
 *
 */
#include <cstdint>

using namespace std;

class Solution {
public:
	uint32_t reverseBits(uint32_t n) {
		uint32_t res = 0;
		for (int i = 0; i < 32 && n > 0; i++) {
			// 位与1用来取某一位，位或0用来存某一位
			res |= (n & 1) << (31 - i);
			n >>= 1;
		}
		return res;
	}
};