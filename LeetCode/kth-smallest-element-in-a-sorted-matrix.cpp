/**
 * @file kth-smallest-element-in-a-sorted-matrix.cpp
 * @author your name (you@domain.com)
 * @brief 378. 有序矩阵中第 K 小的元素
 * @version 0.1
 * @date 2022-08-03
 * @remark https://leetcode.cn/problems/kth-smallest-element-in-a-sorted-matrix/
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {
        vector<int> nums = vector<int>();
        for (size_t i = 0; i < matrix.size(); i++)
            for (size_t j = 0; j < matrix.size(); j++)
                nums.emplace_back(matrix[i][j]);
        sort(nums.begin(), nums.end());
        return nums[k - 1];        
    }
};

int main()
{
    vector<vector<int>> matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
    cout << Solution().kthSmallest(matrix, 16) << "\n";
    cout << Solution().kthSmallest(matrix, 19) << "\n";
    cout << Solution().kthSmallest(matrix, 23) << "\n";
    return 0;
}
