/**
 * @file add-two-numbers.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 2. 两数相加
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/add-two-numbers/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if (l1 == nullptr)
			return l2;
		if (l2 == nullptr)
			return l1;
		ListNode* head = new ListNode(0), * last = head;
		int carry = 0;
		while (l1 != nullptr || l2 != nullptr) {
			int v1 = 0, v2 = 0;
			if (l1 != nullptr) {
				v1 = l1->val;
				l1 = l1->next;
			}
			if (l2 != nullptr) {
				v2 = l2->val;
				l2 = l2->next;
			}
			int sum = v1 + v2 + carry;
			carry = sum / 10;
			last->next = new ListNode(sum % 10);
			last = last->next;
		}
		if (carry > 0)
			last->next = new ListNode(carry);
		return head->next;
	}
};