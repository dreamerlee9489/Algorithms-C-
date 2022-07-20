/**
 * @file delete-node-in-a-linked-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 237. 删除链表中的节点
 * @version 0.1
 * @date 2022-04-05
 * @remark https://leetcode-cn.com/problems/delete-node-in-a-linked-list/
 * @copyright Copyright (c) 2022
 * 
 */
#include "./ListNode.hpp"

class Solution
{
public:
    void deleteNode(ListNode *node)
    {
        node->val = node->next->val;
        node->next = node->next->next;
    }
};