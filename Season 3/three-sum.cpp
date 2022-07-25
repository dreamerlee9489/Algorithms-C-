/**
 * @file 3sum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 15. 三数之和
 * @version 0.1
 * @date 2022-07-24
 * @remark https://leetcode.cn/problems/3sum/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        if (nums.size() < 3)
            return vector<vector<int>>();
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++)
        {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int l = i + 1, r = nums.size() - 1;
            while (l < r)
            {
                if (nums[i] + nums[l] + nums[r] == 0)
                {
                    result.emplace_back(vector<int>({nums[i], nums[l], nums[r]}));
                    while (l < r && nums[l] == nums[l + 1])
                        l++;
                    while (l < r && nums[r] == nums[r - 1])
                        r--;
                    l++;
                    r--;
                }
                else if (nums[i] + nums[l] + nums[r] < 0)
                    l++;
                else
                    r--;
            }
        }
        return result;
    }
};