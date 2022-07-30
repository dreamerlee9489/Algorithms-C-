/**
 * @file reverse-linked-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 206. 反转链表
 * @version 0.1
 * @date 2022-07-28
 * @remark https://leetcode.cn/problems/reverse-linked-list/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if(head == nullptr || head->next == nullptr)
            return head;
        ListNode *newHead = reverseList(head->next);
        newHead->next = head;
        head->next = nullptr;
        return newHead;
    }

    ListNode *reverseList1(ListNode *head)
    {
        if(head == nullptr || head->next == nullptr)
            return head;
        ListNode *newHead = head->next;
        head->next = nullptr;
        while (newHead != nullptr)
        {
            ListNode *newNext = newHead->next;
            newHead->next = head;
            head = newHead;
            newHead = newNext;
        }
        return head;
    }
};