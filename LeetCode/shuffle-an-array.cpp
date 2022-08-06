/**
 * @file shuffle-an-array.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 384. 打乱数组
 * @version 0.1
 * @date 2022-08-06
 * @link https://leetcode.cn/problems/shuffle-an-array/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <vector>
#include <random>

using namespace std;

class Solution
{
    vector<int> nums, res;
    uniform_int_distribution<int> d;
    default_random_engine e;

public:
    Solution(vector<int> &nums)
    {
        this->nums = res = nums;
        d = uniform_int_distribution<int>(0, nums.size() - 1);
    }

    vector<int> reset()
    {
        return nums;
    }

    vector<int> shuffle()
    {
        int pivot = d(e);
        int temp = res[0];
        res[0] = res[pivot];
        res[pivot] = temp;
        int left = 0, right = res.size() - 1;
        while (left < right)
        {
            temp = res[left];
            res[left] = res[right];
            res[right] = temp;
            ++left;
            --right;
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums = {0, -12893, 128384};
    Solution sol(nums);
    auto res1 = sol.shuffle();
    auto res2 = sol.reset();
    auto res3 = sol.shuffle();
    auto res4 = sol.shuffle();
    auto res5 = sol.shuffle();
    auto res6 = sol.shuffle();
    auto res7 = sol.shuffle();
    auto res8 = sol.shuffle();
    auto res9 = sol.shuffle();
    return 0;
}
