/**
 * @file intersection-of-two-linked-lists.cpp
 * @author 354149166@qq.com
 * @brief 160. 相交链表
 * @version 0.1
 * @date 2022-07-18
 * @note https://leetcode.cn/problems/intersection-of-two-linked-lists/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        if (headA == nullptr || headB == nullptr)
            return nullptr;
        ListNode *currA = headA, *currB = headB;
        while (currA != currB)
        {
            currA = currA == nullptr ? headB : currA->next;
            currB = currB == nullptr ? headA : currB->next;
        }
        return currA;
    }
};