/**
 * @file powx-n.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 50. Pow(x, n)
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/powx-n/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
class Solution {
public:
    double myPow(double x, int n) {
        long y = n < 0 ? -(long) n : n;
        double res = 1;
        while (y > 0) {
            if (y & 1 == 1)
                res *= x;
            x *= x;
            y >>= 1;
        }
        return n < 0 ? 1 / res : res;
    }

    double myPow1(double x, int n) {
        if (n == 0)
            return 1;
        if (n == -1)
            return 1 / x;
        double half = myPow1(x, n >> 1);
        return n & 1 == 1 ? half * half * x : half * half;
    }

    int powMod(int x, unsigned y, int z) {
        if (z == 0)
            return 0;
        x %= z;
        int res = 1 % z;
        while (y > 0) {
            if (y & 1 == 1)
                res = (res * x) % z;
            x = (x * x) % z;
            y >>= 1;
        }
        return res;
    }

    int powMod1(int x, unsigned y, int z) {
        if (z == 0)
            return 0;
        if (y == 0)
            return 1 % z;
        int half = powMod1(x, y >> 1, z);
        return y & 1 == 0 ? half * half % z : half * half * (x % z) % z;
    }
};
