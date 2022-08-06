/**
 * @file search-a-2d-matrix-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 240. 搜索二维矩阵 II
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/search-a-2d-matrix-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool searchMatrix(vector<vector<int>> &matrix, int target)
    {
        for(const auto &row : matrix)
        {
            const auto iter = lower_bound(row.begin(), row.end(), target);
            if(iter != row.end() && *iter == target)
                return true;
        }
        return false;
    }
};