/**
 * @file palindrome-linked-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 234. 回文链表
 * @version 0.1
 * @date 2022-07-18
 * @remark https://leetcode.cn/problems/palindrome-linked-list/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution
{
    ListNode *middleNode(ListNode *head)
    {
        ListNode *fast = head, *slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    ListNode *reverseList(ListNode *head)
    {
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

public:
    bool isPalindrome(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return true;
        if (head->next->next == nullptr)
            return head->val == head->next->val;
        ListNode *mid = middleNode(head);
        ListNode *rHead = reverseList(mid->next);
        ListNode *lHead = head;
        ListNode *rOldHead = rHead;
        bool result = true;
        while (rHead != nullptr)
        {
            if (lHead->val != rHead->val)
            {
                result = false;
                break;
            }
            rHead = rHead->next;
            lHead = lHead->next;
        }
        reverseList(rOldHead);
        return result;
    }
};