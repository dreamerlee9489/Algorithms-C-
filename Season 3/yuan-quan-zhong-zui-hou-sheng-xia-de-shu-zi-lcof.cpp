/**
 * @file yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 剑指 Offer 62. 圆圈中最后剩下的数字
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
class Solution {
public:
    int lastRemaining(int n, int m) {
        int res = 0;
        for (size_t i = 2; i <= n; i++)
            res = (res + m) % i;
        return res;
    }

    int lastRemaining1(int n, int m) { return n == 1 ? 0 : (lastRemaining1(n - 1, m) + m) % n; }
};