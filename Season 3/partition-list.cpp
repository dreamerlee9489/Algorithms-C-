/**
 * @file partition-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 86. 分隔链表
 * @version 0.1
 * @date 2022-07-18
 * @remark https://leetcode.cn/problems/partition-list/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution
{
public:
    ListNode *partition(ListNode *head, int x)
    {
        if (head == nullptr)
            return nullptr;
        ListNode *lHead = new ListNode(0), *lTail = lHead;
        ListNode *rHead = new ListNode(0), *rTail = rHead;
        while (head != nullptr)
        {
            if (head->val < x)
            {
                lTail->next = head;
                lTail = head;
            }
            else
            {
                rTail->next = head;
                rTail = head;
            }
            head = head->next;
        }
        rTail->next = nullptr;
        lTail->next = rHead->next;
        return lHead->next;
    }
};