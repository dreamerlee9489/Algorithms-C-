/**
 * @file intersection-of-two-arrays-ii.cpp
 * @author your name (you@domain.com)
 * @brief 350. 两个数组的交集 II
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/intersection-of-two-arrays-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution
{
public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> res;
        unordered_map<int, int> map1, map2;
        for(int n : nums1)
            map1[n]++;
        for(int n : nums2)
            map2[n]++;
        for(auto p : map1)
        {
            if(map2.find(p.first) != map2.end())
            {
                int count = min(map1[p.first], map2[p.first]);
                for (int i = 0; i < count; i++)
                    res.emplace_back(p.first);
            }
        }
        return res;
    }
};