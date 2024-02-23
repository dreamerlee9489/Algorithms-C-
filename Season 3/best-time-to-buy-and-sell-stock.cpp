/**
 * @file best-time-to-buy-and-sell-stock.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 121. 买卖股票的最佳时机
 * @version 0.1
 * @date 2022-07-21
 * @link https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <climits> // 为了使用INT_MAX

 /**
  * 为了解决这个问题，我们需要找出给定价格数组中的最大差值（即在后面的时间点上的最大价格与前面时间点上的最小价格之差）。我们可以通过一次遍历来完成这个任务，同时跟踪我们遇到的最小价格和最大利润。
  * 解题技巧总结：
  * 初始化两个变量，一个用于跟踪到目前为止的最小价格minPrice（初始化为INT_MAX，即最大整数值），另一个用于跟踪到目前为止的最大利润maxProfit（初始化为0）。
  * 遍历价格数组prices，对于每一天：
  * 	更新minPrice为当前价格和之前的minPrice中的较小者。
  * 	计算如果在今天卖出的利润（当前价格减去minPrice），更新maxProfit为这个利润和之前的maxProfit中的较大者。
  * 遍历结束后，maxProfit将包含最大利润值。
  * 返回maxProfit。
  *
  */
class Solution {
public:
	int maxProfit(std::vector<int>& prices) {
		int minPrice = INT_MAX;
		int maxProfit = 0;
		for (int price : prices) {
			// 更新到目前为止的最小价格
			minPrice = std::min(minPrice, price);
			// 更新到目前为止的最大利润
			maxProfit = std::max(maxProfit, price - minPrice);
		}
		return maxProfit;
	}
};