/**
 * @file three-sum.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 15. 三数之和
 * @version 0.1
 * @date 2022-07-31
 * @link https://leetcode.cn/problems/3sum/ @endlink
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
        vector<vector<int>> res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if(i > 0 && nums[i] == nums[i - 1])
                continue;
            int l = i + 1, r = nums.size() - 1;
            while (l < r)
            {
                if(nums[i] + nums[l] + nums[r] < 0)    
                    l++;
                else if(nums[i] + nums[l] + nums[r] > 0)
                    r--;
                else
                {
                    res.emplace_back(vector<int>({nums[i], nums[l], nums[r]}));
                    while (l < r && nums[++l] == nums[l - 1]);
                    while (l < r && nums[--r] == nums[r + 1]);
                }
            }
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    auto res1 = Solution().threeSum(nums1);
    vector<int> nums2 = {1, 2, -2, -1};
    auto res2 = Solution().threeSum(nums2);
    vector<int> nums3 = {-1, 0, 1, 0};
    auto res3 = Solution().threeSum(nums3);
    vector<int> nums4 = {-4, -2, 1, -5, -4, -4, 4, -2, 0, 4, 0, -2, 3, 1, -5, 0};
    auto res4 = Solution().threeSum(nums4);
    vector<int> nums5 = {-4, -2, -1};
    auto res5 = Solution().threeSum(nums5);
    return 0;
}
