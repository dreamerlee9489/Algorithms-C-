/**
 * @file maximum-subarray.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 53. 最大子数组和
 * @version 0.1
 * @date 2022-07-31
 * @link https://leetcode.cn/problems/maximum-subarray/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        int begin = 0, sum = 0, max = nums[0];
        while (begin < nums.size())
        {
            while (nums[begin] < 0 && begin < nums.size() - 1)
                if (nums[++begin] > max)
                    max = nums[begin];
            int end = begin;
            while (end < nums.size())
            {
                if (sum + nums[end] <= 0)
                {
                    sum = 0;
                    break;
                }
                else
                {
                    sum += nums[end];
                    end++;
                    if (sum > max)
                        max = sum;
                }
            }
            begin = end + 1;
        }
        return max;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << Solution().maxSubArray(nums1) << endl;
    vector<int> nums2 = {5, 4, -1, 7, 8};
    cout << Solution().maxSubArray(nums2) << endl;
    vector<int> nums3 = {-2, -1, -2, -10, 0, -5};
    cout << Solution().maxSubArray(nums3) << endl;
    vector<int> nums4 = {1};
    cout << Solution().maxSubArray(nums4) << endl;
    return 0;
}
