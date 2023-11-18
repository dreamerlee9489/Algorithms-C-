/**
 * @file rotate-image.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 48. 旋转图像
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/rotate-image/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		auto temp = matrix;
		for (size_t r = 0; r < matrix.size(); r++)
			for (size_t c = 0; c < matrix.size(); c++)
				matrix[c][matrix.size() - 1 - r] = temp[r][c];
	}
};

int main(int argc, char const* argv[]) {
	vector<vector<int>> matrix = {
		{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16} };
	Solution().rotate(matrix);
	return 0;
}
