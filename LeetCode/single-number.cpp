/**
 * @file single-number.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 136. 只出现一次的数字
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/single-number/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        if (nums.size() > 1)
        {
            sort(nums.begin(), nums.end());
            for (int i = 0; i < nums.size(); i += 2)
                if (nums[i] != nums[i + 1])
                    return nums[i];
        }
        return nums[0];
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums = {4, 1, 2, 1, 2};
    cout << Solution().singleNumber(nums) << "\n";
    return 0;
}
