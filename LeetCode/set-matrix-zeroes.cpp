/**
 * @file set-matrix-zeroes.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 73. 矩阵置零
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/set-matrix-zeroes/
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
	void setZeroes(vector<vector<int>>& matrix) {
		unordered_map<int, vector<int>> _map;
		for (int r = 0; r < matrix.size(); r++)
			for (int c = 0; c < matrix[0].size(); c++)
				if (matrix[r][c] == 0)
					_map[r].emplace_back(c);
		for (auto p : _map) {
			for (int c = 0; c < matrix[0].size(); c++)
				matrix[p.first][c] = 0;
			for (int c : p.second)
				for (int r = 0; r < matrix.size(); r++)
					matrix[r][c] = 0;
		}
	}
};