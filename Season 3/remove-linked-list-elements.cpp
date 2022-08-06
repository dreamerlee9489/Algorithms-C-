/**
 * @file remove-linked-list-elements.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 203. 移除链表元素
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/remove-linked-list-elements/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution {
public:
    ListNode *removeElements(ListNode *head, int val) {
        if (head == nullptr)
            return nullptr;
        ListNode *newHead = new ListNode(0);
        ListNode *newTail = newHead;
        while (head != nullptr) {
            if (head->val != val)
                newTail = newTail->next = head;
            head = head->next;
        }
        newTail->next = nullptr;
        return newHead->next;
    }
};