/**
 * @file best-time-to-buy-and-sell-stock.cpp
 * @author your name (you@domain.com)
 * @brief 121. 买卖股票的最佳时机
 * @version 0.1
 * @date 2022-07-21
 * @remark https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        if(prices.empty())
            return 0;
        int minPrice_ = prices[0], maxProfit_ = 0;
        for (int i = 1; i < prices.size(); ++i)
        {
            if(prices[i] < minPrice_)
                minPrice_ = prices[i];
            else
                maxProfit_ = max(maxProfit_, prices[i] - minPrice_);
        }
        return maxProfit_;
    }
};