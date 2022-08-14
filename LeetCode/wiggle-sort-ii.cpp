/**
 * @file wiggle-sort-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 324. 摆动排序 II
 * @version 0.1
 * @date 2022-08-14
 * @link https://leetcode.cn/problems/wiggle-sort-ii/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    void wiggleSort(vector<int> &nums)
    {
        vector<int> temp(nums);
        sort(temp.begin(), temp.end());
        int left = (nums.size() - 1) / 2, right = nums.size() - 1;
        for (int i = 0; i < nums.size(); i++)
            nums[i] = (i & 1) ? temp[right--] : temp[left--];
    }
};