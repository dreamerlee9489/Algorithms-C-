/**
 * @file maximum-product-subarray.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 152. 乘积最大子数组
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/maximum-product-subarray/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int> &nums) {
        vector<int> maxP(nums), minP(nums);
        for (int i = 1; i < nums.size(); ++i) {
            maxP[i] = max(maxP[i - 1] * nums[i], max(nums[i], minP[i - 1] * nums[i]));
            minP[i] = min(minP[i - 1] * nums[i], min(nums[i], maxP[i - 1] * nums[i]));
        }
        return *max_element(maxP.begin(), maxP.end());
    }
};

int main(int argc, char const *argv[]) {
    vector<int> nums = {5, 6, -3, 4, -3};
    cout << Solution().maxProduct(nums) << "\n";
    return 0;
}
