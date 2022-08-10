/**
 * @file gas-station.cpp
 * @author your name (you@domain.com)
 * @brief 134. 加油站
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/gas-station/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
using namespace std;

class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int pos = 0;
        while (pos < gas.size())
        {
            int gasSum = gas[pos];
            int costSum = cost[pos];
            int step = 0;
            while (step < gas.size())
            {
                if(gasSum < costSum)
                    break;
                ++step;
                int curPos = (pos + step) % gas.size();
                gasSum += gas[curPos];
                costSum += cost[curPos];
            }
            if(step == gas.size())
                return pos;
            else
                pos += step + 1;
        }
        return -1;
    }
};