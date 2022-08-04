/**
 * @file the-skyline-problem.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 218. 天际线问题
 * @version 0.1
 * @date 2022-08-03
 * @link https://leetcode.cn/problems/the-skyline-problem/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> getSkyline(vector<vector<int>> &buildings)
    {
    }
};

int main(int argc, char const *argv[])
{
    vector<vector<int>> buildings = {{2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    auto res = Solution().getSkyline(buildings);
    return 0;
}
