/**
 * @file maximum-binary-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 654. 最大二叉树
 * @version 0.1
 * @date 2022-07-19
 * @remark https://leetcode.cn/problems/maximum-binary-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <stack>
#include "./TreeNode.hpp"
using namespace std;

class Solution
{
    TreeNode *findRoot(vector<int> &nums, int l, int r)
    {
        if (l == r)
            return nullptr;
        int maxIdx = l;
        for (int i = l + 1; i < r; i++)
            if (nums[i] > nums[maxIdx])
                maxIdx = i;
        TreeNode *root = new TreeNode(nums[maxIdx]);
        root->left = findRoot(nums, l, maxIdx);
        root->right = findRoot(nums, maxIdx + 1, r);
        return root;
    }

public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        if (nums.empty())
            return nullptr;
        return findRoot(nums, 0, nums.size());
    }

    vector<int> parentIndexes(vector<int> &nums)
    {
        vector<int> lis = vector<int>(nums.size(), -1);
        vector<int> ris = vector<int>(nums.size(), -1);
        vector<int> pis = vector<int>(nums.size());
        stack<int> stk = stack<int>();
        for (size_t i = 0; i < nums.size(); i++)
        {
            while (!stk.empty() && nums[i] > nums[stk.top()])
            {
                ris[stk.top()] = i;
                stk.pop();
            }
            if (!stk.empty())
                lis[i] = stk.top();
            stk.push(i);
        }
        for (size_t i = 0; i < pis.size(); i++)
        {
            if (lis[i] == -1 && ris[i] == -1)
            {
                pis[i] = -1;
                continue;
            }
            if (lis[i] == -1)
                pis[i] = ris[i];
            else if (ris[i] == -1)
                pis[i] = lis[i];
            else if (nums[lis[i]] < nums[ris[i]])
                pis[i] = lis[i];
            else
                pis[i] = ris[i];
        }
        return pis;
    }
};
