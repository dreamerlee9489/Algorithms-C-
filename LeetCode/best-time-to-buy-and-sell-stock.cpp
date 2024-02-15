/**
 * @file best-time-to-buy-and-sell-stock.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 121. 买卖股票的最佳时机
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int price = prices[0], profit = 0;
		for (int i = 1; i < prices.size(); i++) {
			if (prices[i] < price)
				price = prices[i];
			profit = max(profit, prices[i] - price);
		}
		return profit;
	}
};