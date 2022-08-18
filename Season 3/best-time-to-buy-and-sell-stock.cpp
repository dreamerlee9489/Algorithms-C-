/**
 * @file best-time-to-buy-and-sell-stock.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 121. 买卖股票的最佳时机
 * @version 0.1
 * @date 2022-07-21
 * @link https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        if (prices.empty())
            return 0;
        int minPrice = prices[0], maxProfit = 0;
        for (int i = 1; i < prices.size(); ++i) {
            if (prices[i] < minPrice)
                minPrice = prices[i];
            else
                maxProfit = max(maxProfit, prices[i] - minPrice);
        }
        return maxProfit;
    }
};