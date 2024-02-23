/**
 * @file spiral-matrix.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 54. 螺旋矩阵
 * @version 0.1
 * @date 2022-07-24
 * @link https://leetcode.cn/problems/spiral-matrix/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
using namespace std;

/**
 * 解题技巧总结：
 * 这道题目要求按顺时针螺旋顺序遍历矩阵，并返回遍历的所有元素。可以通过模拟螺旋遍历的过程来解决这个问题。以下是解决这个问题的关键步骤和技巧：
 * 定义边界：定义四个边界变量top、bottom、left和right，分别代表矩阵的上、下、左、右边界。
 * 循环遍历：在矩阵中顺时针遍历，直到遍历完所有的元素。这通常涉及四个步骤：从左到右、从上到下、从右到左、从下到上。
 * 更新边界：在每次遍历一个边界后，需要更新边界变量以缩小遍历范围。例如，遍历完上边界后，top边界需要向下移动；遍历完右边界后，right边界需要向左移动，以此类推。
 * 注意边界条件：在每一步遍历过程中，需要检查是否达到了边界条件，如是否还有更多的行或列可以遍历。
 * 时间和空间复杂度：时间复杂度为O(m * n)，其中m是矩阵的行数，n是矩阵的列数，因为我们需要遍历矩阵中的每个元素。空间复杂度为O(1)，如果不考虑输出数组的空间占用，则算法本身只需要常数级别的额外空间。
 *
 */
class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		vector<int> result;
		if (matrix.empty()) return result;

		int m = matrix.size(), n = matrix[0].size();
		int top = 0, bottom = m - 1, left = 0, right = n - 1;

		while (top <= bottom && left <= right) {
			// 从左到右遍历上边界
			for (int j = left; j <= right; ++j) {
				result.push_back(matrix[top][j]);
			}
			top++;

			// 从上到下遍历右边界
			for (int i = top; i <= bottom; ++i) {
				result.push_back(matrix[i][right]);
			}
			right--;

			if (top <= bottom) {
				// 从右到左遍历下边界
				for (int j = right; j >= left; --j) {
					result.push_back(matrix[bottom][j]);
				}
				bottom--;
			}

			if (left <= right) {
				// 从下到上遍历左边界
				for (int i = bottom; i >= top; --i) {
					result.push_back(matrix[i][left]);
				}
				left++;
			}
		}

		return result;
	}
};