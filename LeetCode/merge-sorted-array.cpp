/**
 * @file merge-sorted-array.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 88. 合并两个有序数组
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/merge-sorted-array/ @endlink
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
        int l = 0, r = 0, i = 0;
        vector<int> temp = vector<int>(m);
        for (size_t i = 0; i < m; i++)
            temp[i] = nums1[i];
        while (l < m && r < n)
        {
            if(temp[l] <= nums2[r])
            {
                nums1[i] = temp[l];
                l++;
            }
            else
            {
                nums1[i] = nums2[r];
                r++;
            }
            i++;
        }
        for (int j = l; j < m; j++)
        {
            nums1[i] = temp[j];     
            i++;
        }   
        for (int k = r; k < n; k++)
        {
            nums1[i] = nums2[k]; 
            i++;
        }  
    }
};