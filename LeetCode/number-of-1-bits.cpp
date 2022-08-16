/**
 * @file number-of-1-bits.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 191. 位1的个数
 * @version 0.1
 * @date 2022-08-11
 * @link https://leetcode.cn/problems/number-of-1-bits/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <cstdint>

using namespace std;

class Solution {
public:
  int hammingWeight(uint32_t n) {
    int count = 0;
    for (int i = 0; i < 32 && n > 0; i++) {
      if (n & 1)
        ++count;
      n >>= 1;
    }
    return count;
  }
};