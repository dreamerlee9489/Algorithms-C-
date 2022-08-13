/**
 * @file find-the-celebrity.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 277. 搜寻名人
 * @version 0.1
 * @date 2022-08-13
 * @link https://leetcode.cn/problems/find-the-celebrity/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <unordered_set>
#include <numeric>
using namespace std;

bool knows(int a, int b);

class Solution
{
public:
    int findCelebrity(int n)
    {
        int res = 0;
        for (int i = i; i < n; i++)
            if(knows(res, i))
                res = i;
        for (int i = 0; i < n; i++)
            if(res != i && (knows(res, i) || !knows(i, res)))
                return -1;
        return res;
    }
};

class Solution1
{
    vector<vector<bool>> _graph;

public:
    int findCelebrity(int n)
    {
        _graph = vector<vector<bool>>(n, vector<bool>(n));
        unordered_set<int> set;
        vector<int> indexs;
        for (int i = 0; i < n; i++)
            set.emplace(i);
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if (r != c)
                {
                    if (knows(r, c))
                        set.erase(r);
                    else
                        set.erase(c);
                }
            }
        }
        return set.size() == 1 ? *set.begin() : -1;
    }
};