/**
 * @file odd-even-linked-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 328. 奇偶链表
 * @version 0.1
 * @date 2022-08-14
 * @link https://leetcode.cn/problems/odd-even-linked-list/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution
{
public:
    ListNode *oddEvenList(ListNode *head)
    {
        if(!head)
            return nullptr;
        ListNode *head1 = head, *head2 = head->next;
        ListNode *tail1 = head1, *tail2 = head2;
        while (tail1->next && tail2->next)
        {
            tail1->next = tail2->next;
            tail1 = tail1->next;
            tail2->next = tail1->next;
            tail2 = tail2->next;
        }
        tail1->next = head2;
        return head1;
    }
};