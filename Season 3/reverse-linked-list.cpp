/**
 * @file reverse-linked-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 206. 反转链表
 * @version 0.1
 * @date 2022-04-05
 * @remark https://leetcode-cn.com/problems/reverse-linked-list/
 * @copyright Copyright (c) 2022
 * 
 */
#include "./ListNode.hpp"

class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *newHead = nullptr;
        while (head != nullptr)
        {
            ListNode *temp = head->next;
            head->next = newHead;
            newHead = head;
            head = temp;
        }
        return newHead;
    }
};