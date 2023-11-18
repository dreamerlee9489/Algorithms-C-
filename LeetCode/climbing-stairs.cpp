/**
 * @file climbing-stairs.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 70. 爬楼梯
 * @version 0.1
 * @date 2022-08-03
 * @link https://leetcode.cn/problems/climbing-stairs/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
	/**
	 * @brief 动态规划模拟递归
	 * @param n
	 * @return int
	 */
	int climbStairs(int n) {
		vector<int> res = vector<int>(n + 1, 1);
		for (size_t i = 2; i < res.size(); i++)
			res[i] = res[i - 1] + res[i - 2];
		return res[n];
	}
};