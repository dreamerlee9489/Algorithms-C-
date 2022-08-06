/**
 * @file spiral-matrix.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 54. 螺旋矩阵
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/spiral-matrix/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        if (matrix.empty())
            return vector<int>();
        vector<int> result;
        int top = 0, bottom = matrix.size() - 1;
        int left = 0, right = matrix[0].size() - 1;
        while (top <= bottom && left <= right) {
            for (int i = left; i <= right; ++i)
                result.emplace_back(matrix[top][i]);
            top++;
            for (int i = top; i <= bottom; ++i)
                result.emplace_back(matrix[i][right]);
            right--;
            if (top > bottom || left > right)
                break;
            for (int i = right; i >= left; --i)
                result.emplace_back(matrix[bottom][i]);
            bottom--;
            for (int i = bottom; i >= top; --i)
                result.emplace_back(matrix[i][left]);
            left++;
        }
        return result;
    }
};