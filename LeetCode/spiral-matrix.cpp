/**
 * @file spiral-matrix.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 54. 螺旋矩阵
 * @version 0.1
 * @date 2022-08-02
 * @link https://leetcode.cn/problems/spiral-matrix/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> res;
		int top = 0, bottom = matrix.size() - 1;
		int left = 0, right = matrix[0].size() - 1;
		while (top <= bottom && left <= right) {
			for (int i = left; i <= right; i++)
				res.emplace_back(matrix[top][i]);
			if (++top > bottom)
				break;
			for (int i = top; i <= bottom; i++)
				res.emplace_back(matrix[i][right]);
			if (--right < left)
				break;
			for (int i = right; i >= left; i--)
				res.emplace_back(matrix[bottom][i]);
			if (--bottom < top)
				break;
			for (int i = bottom; i >= top; i--)
				res.emplace_back(matrix[i][left]);
			if (++left > right)
				break;
		}
		return res;
	}
};

int main(int argc, char const* argv[]) {
	vector<vector<int>> matrix1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
	auto res1 = Solution().spiralOrder(matrix1);
	vector<vector<int>> matrix2 = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
	auto res2 = Solution().spiralOrder(matrix2);
	vector<vector<int>> matrix3 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12} };
	auto res3 = Solution().spiralOrder(matrix3);
	return 0;
}
