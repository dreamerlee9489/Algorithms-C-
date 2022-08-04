/**
 * @file reverse-integer.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 7. 整数反转
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/reverse-integer/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

class Solution
{
public:
    int reverse(int x)
    {
        int res = 0;
        while (x != 0)
        {
            long prevRes = res;
            int mod = x % 10;
            res = prevRes * 10 + mod;
            if((res - mod) / 10 != prevRes)
                return 0;
            x /= 10;
        }
        return res;
    }
};


int main(int argc, char const *argv[])
{
    cout << Solution().reverse(2147483647) << "\n";
    cout << Solution().reverse(-2147483648) << "\n";
    cout << "INT_MAX=" << INT_MAX << " " << Solution().reverse(INT_MAX) << "\n";
    return 0;
}
