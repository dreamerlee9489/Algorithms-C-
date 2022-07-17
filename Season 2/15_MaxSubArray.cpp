#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * @brief 最大连续子序列和
 * @remark 动态规划
 * @date 2022-07-08 
 * @param nums
 * @return int
 */
int maxSubArray(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    int dp = nums[0];
    int max = dp;
    for(int i = 1; i < nums.size(); i++)
    {
        dp = dp <= 0 ? nums[i] : (dp + nums[i]);
        max = std::max(dp, max);
    }
    return max;
}

int main(int argc, char const *argv[])
{
    // 想要传递引用,必须给实参取名
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << maxSubArray(nums) << "\n";
    return 0;
}
