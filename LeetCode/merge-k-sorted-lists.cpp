/**
 * @file merge-k-sorted-lists.cpp
 * @author your name (you@domain.com)
 * @brief 23. 合并K个升序链表
 * @version 0.1
 * @date 2022-08-01
 * @remark https://leetcode.cn/problems/merge-k-sorted-lists/
 * @copyright Copyright (c) 2022
 *
 */
#include "ListNode.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        if (lists.size() == 0)
            return nullptr;
        if (lists.size() == 1)
            return lists[0];
        ListNode *res = new ListNode(), *tail = res, *p = nullptr;
        vector<int> nums;
        for (size_t i = 0; i < lists.size(); i++)
        {
            while(lists[i] != nullptr)
            {
                nums.emplace_back(lists[i]->val);
                lists[i] = lists[i]->next;
            }
        }
        sort(nums.begin(), nums.end());
        for (size_t i = 0; i < nums.size(); i++)
        {
            tail->next = new ListNode(nums[i]);
            tail = tail->next;
        }        
        return res->next;
    }

    ListNode *mergeKLists_my(vector<ListNode *> &lists)
    {
        if (lists.size() == 0)
            return nullptr;
        if (lists.size() == 1)
            return lists[0];
        ListNode *res = new ListNode(), *tail = res, *minNode = res;
        while (minNode != nullptr)
        {
            int min = INT_MAX, minIdx = 0;
            for (int i = 0; i < lists.size(); i++)
            {
                if (lists[i] != nullptr && lists[i]->val < min)
                {
                    min = lists[i]->val;
                    minIdx = i;
                    minNode = lists[i];
                }
            }
            minNode = lists[minIdx];
            if (lists[minIdx] != nullptr)
                lists[minIdx] = lists[minIdx]->next;
            if (min < INT_MAX)
            {
                tail->next = new ListNode(min);
                tail = tail->next;
            }
        }
        return res->next;
    }
};

int main(int argc, char const *argv[])
{
    // ListNode *l1 = new ListNode(1);
    // l1->next = new ListNode(4);
    // l1->next->next = new ListNode(5);
    // ListNode *l2 = new ListNode(1);
    // l2->next = new ListNode(3);
    // l2->next->next = new ListNode(4);
    // ListNode *l3 = new ListNode(2);
    // l3->next = new ListNode(6);
    // vector<ListNode *> lists = {l1, l2, l3};

    ListNode *l1 = nullptr;
    ListNode *l2 = new ListNode(1);
    vector<ListNode *> lists = {l1, l2};

    ListNode *res = Solution().mergeKLists(lists);
    while (res != nullptr)
    {
        cout << res->val << " ";
        res = res->next;
    }
    return 0;
}
