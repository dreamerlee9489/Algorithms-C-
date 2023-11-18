/**
 * @file best-time-to-buy-and-sell-stock-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 122. 买卖股票的最佳时机 II
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
 * @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int profit = 0, price = 0;
		for (int i = 0; i < prices.size() - 1; i++)
			if (prices[i] < prices[i + 1])
				profit += prices[i + 1] - prices[i];
		return profit;
	}
};