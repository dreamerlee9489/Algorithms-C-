/**
 * @file sort-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 148. 排序链表
 * @version 0.1
 * @date 2022-08-03
 * @link https://leetcode.cn/problems/sort-list/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    ListNode *sortList(ListNode *head)
    {
        vector<int> vec;
        ListNode *temp = head;
        while (temp != nullptr)
        {
            vec.emplace_back(temp->val);
            temp = temp->next;
        }
        sort(vec.begin(), vec.end());
        temp = head;
        for (size_t i = 0; i < vec.size(); i++)
        {
            temp->val = vec[i];
            temp = temp->next;
        }
        return head;
    }
};

int main(int argc, char const *argv[])
{
    ListNode *head = new ListNode(-1);
    head->next = new ListNode(5);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(0);
    ListNode *res = Solution().sortList(head);
    return 0;
}
