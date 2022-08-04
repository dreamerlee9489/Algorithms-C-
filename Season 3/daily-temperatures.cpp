/**
 * @file daily-temperatures.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 739. 每日温度
 * @version 0.1
 * @date 2022-07-19
 * @link https://leetcode.cn/problems/daily-temperatures/ @endlink
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
        vector<int> vals = vector<int>(temperatures.size());
        for(int i = vals.size() - 2; i >= 0; i--)
        {
            int j = i + 1;
            while (true)
            {
                if(temperatures[i] < temperatures[j])
                {
                    vals[i] = j - i;
                    break;
                }
                else if(vals[j] == 0)
                {
                    vals[i] = 0;
                    break;
                }
                j += vals[j];
            }
        }
        return vals;
    }

    vector<int> dailyTemperatures1(vector<int> &temperatures)
    {
        if (temperatures.empty())
            return vector<int>();
        vector<int> vals = vector<int>(temperatures.size());
        stack<int> stk = stack<int>();
        for (size_t i = 0; i < temperatures.size(); i++)
        {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()])
            {
                vals[stk.top()] = i - stk.top();
                stk.pop();
            }
            stk.push(i);
        }
        return vals;
    }
};