/**
 * @file linked-list-cycle.cpp
 * @author 354149166@qq.com
 * @brief 141. 环形链表
 * @version 0.1
 * @date 2022-04-05
 * @note https://leetcode-cn.com/problems/linked-list-cycle/
 * @copyright Copyright (c) 2022
 * 
 */
#include "./ListNode.hpp"

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return false;
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }
};