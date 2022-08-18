/**
 * @file permutations.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 46. 全排列
 * @version 0.1
 * @date 2022-07-23
 * @link https://leetcode.cn/problems/permutations/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>

using namespace std;

class Solution {
    void dfs(int index, vector<int> &nums, vector<vector<int>> &list) {
        if (index == nums.size()) {
            list.emplace_back(nums);
            return;
        }
        for (int i = index; i < nums.size(); ++i) {
            swap(nums, index, i);
            dfs(index + 1, nums, list);
            swap(nums, index, i);
        }
    }

    void swap(vector<int> &nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

public:
    vector<vector<int>> permute(vector<int> &nums) {
        if (nums.empty())
            return vector<vector<int>>();
        vector<vector<int>> list;
        dfs(0, nums, list);
        return list;
    }
};

class Solution2 {
    vector<vector<int>> list;
    vector<int> nums, result;

    void dfs(int index) {
        if (index == nums.size()) {
            list.emplace_back(result);
            return;
        }
        for (int num: nums) {
            if (!contains(result, num)) {
                result.emplace_back(num);
                dfs(index + 1);
                // result.erase(result.end());
                result.pop_back();
            }
        }
    }

    bool contains(vector<int> &vals, int num) {
        for (int val: vals)
            if (val == num)
                return true;
        return false;
    }

public:
    vector<vector<int>> permute(vector<int> &nums) {
        if (nums.empty())
            return vector<vector<int>>();
        this->nums = nums;
        dfs(0);
        return list;
    }
};

class Solution1 {
    vector<vector<int>> list;
    vector<int> nums, result;
    vector<bool> used;

    void dfs(int index) {
        if (index == nums.size()) {
            list.emplace_back(result);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (!used[i]) {
                result[index] = nums[i];
                used[i] = true;
                dfs(index + 1);
                used[i] = false;
            }
        }
    }

public:
    vector<vector<int>> permute(vector<int> &nums) {
        if (nums.empty())
            return vector<vector<int>>();
        this->nums = nums;
        this->result = vector<int>(nums.size());
        this->used = vector<bool>(nums.size());
        dfs(0);
        return list;
    }
};