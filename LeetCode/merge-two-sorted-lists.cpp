/**
 * @file merge-two-sorted-lists.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 21. 合并两个有序链表
 * @version 0.1
 * @date 2022-08-01
 * @link https://leetcode.cn/problems/merge-two-sorted-lists/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution
{
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *res = new ListNode(), *tail = res;
        while (list1 != nullptr && list2 != nullptr)
        {
            if (list1->val < list2->val)
            {
                tail->next = list1;
                tail = tail->next;
                list1 = list1->next;
                tail->next = nullptr;
            }
            else if (list1->val > list2->val)
            {
                tail->next = list2;
                tail = tail->next;
                list2 = list2->next;
                tail->next = nullptr;
            }
            else
            {
                tail->next = list1;
                tail = tail->next;
                list1 = list1->next;
                tail->next = list2;
                tail = tail->next;
                list2 = list2->next;
                tail->next = nullptr;
            }
        }
        if (list1 != nullptr)
            tail->next = list1;
        else
            tail->next = list2;
        return res->next;
    }
};

int main(int argc, char const *argv[])
{
    ListNode *l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    ListNode *l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    ListNode *res = Solution().mergeTwoLists(l1, l2);
    return 0;
}
