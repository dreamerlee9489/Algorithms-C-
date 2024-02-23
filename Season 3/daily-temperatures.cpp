/**
 * @file daily-temperatures.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 739. 每日温度
 * @version 0.1
 * @date 2022-07-19
 * @link https://leetcode.cn/problems/daily-temperatures/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <stack>

 /**
  * 为了解决这个问题，我们可以使用一个栈来跟踪温度的索引。栈中的索引对应的温度是按降序排列的。当我们遍历数组时，对于每一天的温度，我们将其与栈顶索引对应的温度比较。如果当前天的温度更高，那么我们找到了栈顶索引所代表的那天之后的更高温度。我们将持续这样做直到当前天的温度不再比栈顶索引对应的温度高或者栈为空，然后将当前天的索引压入栈中。
  * 解题技巧总结：
  * 初始化一个栈stack来存储温度的索引，这些索引对应的温度是我们还没有找到下一个更高温度的日子。
  * 初始化一个结果数组answer，其长度与temperatures数组相同，并用0填充，因为默认值是0（表示没有更高的温度）。
  * 遍历temperatures数组，对于每个元素，执行以下步骤：
  * 	同时检查栈不为空且当前元素的温度大于栈顶索引对应的温度。
  * 	如果是，说明我们找到了一个更高的温度。弹出栈顶元素prevIndex，并计算两个索引之间的差距，将其作为结果数组中prevIndex位置的值。
  * 	重复上述过程，直到栈为空或当前元素的温度不大于栈顶索引对应的温度。
  * 	将当前元素的索引压入栈中。
  * 遍历结束后，返回结果数组answer。
  *
  */
class Solution {
public:
	std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
		std::vector<int> answer(temperatures.size(), 0);
		std::stack<int> indexStack; // 用于存储索引的栈

		for (int i = 0; i < temperatures.size(); ++i) {
			// 当前温度比栈顶索引对应的温度要高
			while (!indexStack.empty() && temperatures[i] > temperatures[indexStack.top()]) {
				int prevIndex = indexStack.top();
				indexStack.pop();
				answer[prevIndex] = i - prevIndex; // 计算两个索引之间的差距
			}
			// 将当前索引压入栈中
			indexStack.push(i);
		}

		return answer;
	}
};