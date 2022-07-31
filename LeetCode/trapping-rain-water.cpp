/**
 * @file trapping-rain-water.cpp
 * @author your name (you@domain.com)
 * @brief 42. 接雨水
 * @version 0.1
 * @date 2022-07-31
 * @remark https://leetcode.cn/problems/trapping-rain-water/
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        if (height.empty())
            return 0;
        int sum = 0;
        // 动态规划: 利用左右边界推导出lMaxes, rMaxes
        vector<int> lMaxes = vector<int>(height.size(), 0);
        vector<int> rMaxes = vector<int>(height.size(), 0);
        for (int i = 1; i < height.size() - 1; i++)
            lMaxes[i] = max(lMaxes[i - 1], height[i - 1]);
        for (int i = height.size() - 2; i > 0; i--)
            rMaxes[i] = max(rMaxes[i + 1], height[i + 1]);
        for (int i = 1; i < height.size() - 1; i++)
        {
            int lrMin = min(lMaxes[i], rMaxes[i]);
            if(lrMin > height[i])
                sum += lrMin - height[i];
        }
        return sum;
   }
};

int main(int argc, char const *argv[])
{
    vector<int> h1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << Solution().trap(h1) << "\n";
    vector<int> h2 = {4, 2, 0, 3, 2, 5};
    cout << Solution().trap(h2) << "\n";
    return 0;
}
