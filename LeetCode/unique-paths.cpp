/**
 * @file unique-paths.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 62. 不同路径
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/unique-paths/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
	/**
	 * @brief 组合
	 * @param m
	 * @param n
	 * @return (m + n - 2)! / ((m - 1)! * (n - 1)!)
	 */
	int uniquePaths(int m, int n) {
		int res = 1;
		for (int i = n, j = 1; j < m; i++, j++)
			res = res * i / j;
		return res;
	}
};

int main(int argc, char const* argv[]) {
	cout << Solution().uniquePaths(3, 7) << "\n";
	cout << Solution().uniquePaths(3, 3) << "\n";
	cout << Solution().uniquePaths(3, 2) << "\n";
	cout << Solution().uniquePaths(10, 10) << "\n";
	cout << Solution().uniquePaths(16, 16) << "\n";
	return 0;
}
