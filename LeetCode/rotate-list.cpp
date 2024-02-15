/**
 * @file rotate-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 61. 旋转链表
 * @version 0.1
 * @date 2024-02-15
 * @link https://leetcode.cn/problems/rotate-list/description/
 * @copyright Copyright (c) 2024
 * 
 */
#include "./ListNode.hpp"

class Solution {
public:
	ListNode* rotateRight(ListNode* head, int k) {
		if (k == 0 || !head || !head->next) return head;
		int len = 1;
		ListNode* curr = head;
		while (curr->next) {
			curr = curr->next;
			++len;
		}
		curr->next = head;		//形成环
		int steps = len - k % len;
		while (steps--)
			curr = curr->next;
		head = curr->next;
		curr->next = nullptr;	//断开环
		return head;
	}
};