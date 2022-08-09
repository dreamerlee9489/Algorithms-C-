/**
 * @file linked-list-cycle.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 141. 环形链表
 * @version 0.1
 * @date 2022-08-09
 * @link https://leetcode.cn/problems/linked-list-cycle/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast)
                return true;
        }
        return false;
    }
};