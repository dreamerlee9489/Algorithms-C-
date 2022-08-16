/**
 * @file remove-nth-node-from-end-of-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 19. 删除链表的倒数第 N 个结点
 * @version 0.1
 * @date 2022-08-04
 * @link https://leetcode.cn/problems/remove-nth-node-from-end-of-list/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"
#include <vector>

using namespace std;

class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    vector<ListNode *> vec;
    ListNode *p = head;
    while (p != nullptr) {
      vec.emplace_back(p);
      p = p->next;
    }
    if (n < vec.size() && n != 1)
      vec[vec.size() - n - 1]->next = vec[vec.size() - n + 1];
    else if (n == vec.size())
      head = head->next;
    else if (n == 1 && vec.size() > 1)
      vec[vec.size() - 2]->next = nullptr;
    else if (vec.size() == 1)
      return nullptr;
    return head;
  }
};