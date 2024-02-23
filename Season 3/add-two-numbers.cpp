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

/**
 * 初始化一个新链表存储结果，以及一个指针用于构造这个链表，同时初始化一个变量carry用于存储进位，开始时carry为0。
 * 遍历两个链表，直到两个链表都遍历完全。在每一步中：
 * 将两个链表中的当前节点的值相加，如果某个链表的当前节点为空，则将其值视为0。
 * 将上一步的和加上carry值（上一轮的进位）。
 * 更新carry值，如果当前和大于等于10，则carry设为1，否则设为0。
 * 创建一个新节点，值为当前和对10取余（即当前和的个位数），将其加到结果链表的末尾。
 * 如果两个链表都遍历完毕后，carry值不为0，则需要创建一个值为carry的新节点，加到结果链表的末尾。
 * 返回结果链表的头节点。
 *
 */
class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* dummyHead = new ListNode(0); // 创建一个虚拟头节点，方便操作
		ListNode* current = dummyHead;
		int carry = 0; // 初始化进位carry为0
		while (l1 != nullptr || l2 != nullptr) { // 遍历两个链表
			int x = (l1 != nullptr) ? l1->val : 0;
			int y = (l2 != nullptr) ? l2->val : 0;
			int sum = carry + x + y; // 计算两数之和加上进位
			carry = sum / 10; // 计算新的进位
			current->next = new ListNode(sum % 10); // 创建新节点存储和的个位
			current = current->next;
			if (l1 != nullptr) l1 = l1->next;
			if (l2 != nullptr) l2 = l2->next;
		}
		if (carry > 0) { // 如果最后有进位，添加新节点
			current->next = new ListNode(carry);
		}
		ListNode* head = dummyHead->next; // 获取结果链表的头节点
		delete dummyHead; // 删除虚拟头节点
		return head; // 返回结果链表的头节点
	}
};