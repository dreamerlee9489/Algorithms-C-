/**
 * @file pascals-triangle.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 118. 杨辉三角
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/pascals-triangle/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> res;
		for (int i = 0; i < numRows; i++)
			res.emplace_back(vector<int>(i + 1, 1));
		for (int i = 2; i < numRows; i++)
			for (int j = 1; j < res[i].size() - 1; j++)
				res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
		return res;
	}
};

int main(int argc, char const* argv[]) {
	auto res = Solution().generate(5);
	return 0;
}
