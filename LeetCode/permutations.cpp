/**
 * @file permutations.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 46. 全排列
 * @version 0.1
 * @date 2022-08-02
 * @link https://leetcode.cn/problems/permutations/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
    vector<int> nums, vec;
    vector<vector<int>> res;

    bool contains(vector<int> &vec, int val)
    {
        for (size_t i = 0; i < vec.size(); i++)
            if (vec[i] == val)
                return true;
        return false;
    }

    void dfs(int layer)
    {
        if (layer == nums.size())
            res.emplace_back(vec);
        else
        {
            for (size_t i = 0; i < nums.size(); i++)
            {
                if (!contains(vec, nums[i]))
                {
                    vec.emplace_back(nums[i]);
                    dfs(layer + 1);
                    vec.pop_back();
                }
            }
        }
    }

public:
    vector<vector<int>> permute(vector<int> &nums)
    {
        this->nums = nums;
        dfs(0);
        return res;
    }
};

int main(int argc, char const *argv[])
{
    vector<int> nums = {1, 2, 3};
    auto res = Solution().permute(nums);
    return 0;
}
