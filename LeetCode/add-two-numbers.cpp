/**
 * @file add-two-numbers.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 2. 两数相加
 * @version 0.1
 * @date 2022-07-31
 * @link https://leetcode.cn/problems/add-two-numbers/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"
#include <iostream>

using namespace std;

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode *res = new ListNode(0), *tail = res;
    while (l1 != nullptr || l2 != nullptr) {
      int sum = tail->val;
      if (l1 != nullptr)
        sum += l1->val;
      if (l2 != nullptr)
        sum += l2->val;
      if (sum < 10) {
        tail->val = sum;
        // 进位为0，如果下一位还有数字，追加新结点
        if ((l1 != nullptr && l1->next != nullptr) ||
            (l2 != nullptr && l2->next != nullptr))
          tail->next = new ListNode(0);
      } else {
        tail->val = sum - 10;
        // 进位为1，直接追加新结点
        tail->next = new ListNode(1);
      }
      tail = tail->next;
      if (l1 != nullptr)
        l1 = l1->next;
      if (l2 != nullptr)
        l2 = l2->next;
    }
    return res;
  }
};

int main(int argc, char const *argv[]) {
  ListNode *l1_1 = new ListNode(5);
  ListNode *l1_2 = new ListNode(4);
  ListNode *l1_3 = new ListNode(3);
  ListNode *l1_4 = new ListNode(9);
  ListNode *l1_5 = new ListNode(9);
  ListNode *l1_6 = new ListNode(9);
  ListNode *l1_7 = new ListNode(9);
  l1_1->next = l1_2;
  l1_2->next = l1_3;
  l1_3->next = l1_4;
  l1_4->next = l1_5;
  l1_5->next = l1_6;
  l1_6->next = l1_7;
  ListNode *l2_1 = new ListNode(3);
  ListNode *l2_2 = new ListNode(6);
  ListNode *l2_3 = new ListNode(3);
  ListNode *l2_4 = new ListNode(9);
  l2_1->next = l2_2;
  l2_2->next = l2_3;
  l2_3->next = l2_4;
  ListNode *res1 = Solution().addTwoNumbers(l1_1, l2_1);
  while (res1 != nullptr) {
    cout << res1->val;
    res1 = res1->next;
  }
  cout << endl;
  ListNode *l3_1 = new ListNode(2);
  ListNode *l3_2 = new ListNode(4);
  ListNode *l3_3 = new ListNode(3);
  l3_1->next = l3_2;
  l3_2->next = l3_3;
  ListNode *l4_1 = new ListNode(5);
  ListNode *l4_2 = new ListNode(6);
  ListNode *l4_3 = new ListNode(4);
  l4_1->next = l4_2;
  l4_2->next = l4_3;
  ListNode *res2 = Solution().addTwoNumbers(l3_1, l4_1);
  while (res2 != nullptr) {
    cout << res2->val;
    res2 = res2->next;
  }
  return 0;
}
