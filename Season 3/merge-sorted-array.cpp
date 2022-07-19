/**
 * @file merge-sorted-array.cpp
 * @author 354149166@qq.com
 * @brief 合并两个有序数组
 * @version 0.1
 * @date 2022-07-18
 * @note https://leetcode.cn/problems/merge-sorted-array/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
using namespace std;

class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        int i1 = m - 1, i2 = n - 1;
        int cur = nums1.size() - 1;
        while (i2 >= 0)
        {
            if (i1 >= 0 && nums2[i2] < nums1[i1])
                nums1[cur--] = nums1[i1--];
            else
                nums1[cur--] = nums2[i2--];
        }
    }
};