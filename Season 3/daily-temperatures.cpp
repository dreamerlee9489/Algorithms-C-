/**
 * @file daily-temperatures.cpp
 * @author your name (you@domain.com)
 * @brief 739. 每日温度
 * @version 0.1
 * @date 2022-07-19
 * @note https://leetcode.cn/problems/daily-temperatures/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <stack>
using namespace std;

class Solution
{
public:
    vector<int> dailyTemperatures(vector<int> &temperatures)
    {
        if (temperatures.empty())
            return vector<int>();
        vector<int> result_ = vector<int>(temperatures.size());
        stack<int> stack_ = stack<int>();
        for (size_t i = 0; i < temperatures.size(); i++)
        {
            while (!stack_.empty() && temperatures[i] > temperatures[stack_.top()])
            {
                result_[stack_.top()] = i - stack_.top();
                stack_.pop();
            }
            stack_.push(i);
        }
        return result_;
    }
};