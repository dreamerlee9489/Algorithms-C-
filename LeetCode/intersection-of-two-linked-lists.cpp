/**
 * @file intersection-of-two-linked-lists.cpp
 * @author your name (you@domain.com)
 * @brief 160. 相交链表
 * @version 0.1
 * @date 2022-08-10
 * @link https://leetcode.cn/problems/intersection-of-two-linked-lists/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <unordered_set>
#include "./ListNode.hpp"
using namespace std;

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *_p = headA, *_q = headB;
        unordered_set<ListNode*> _set;
        while (_p != nullptr)
        {
            _set.emplace(_p);
            _p = _p->next;
        }
        while (_q != nullptr)
        {
            if(_set.find(_q) != _set.end())
                return _q;
            _q = _q->next;
        }
        return nullptr;
    }
};