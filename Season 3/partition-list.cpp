/**
 * @file partition-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 86. 分隔链表
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/partition-list/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

/**
 * 解题技巧总结：
 * 为了解决这个问题，下面是一些关键点：
 * 保持原始顺序：需要保持小于x的节点和大于等于x的节点在他们各自分区内的原始顺序。
 * 使用哨兵节点：创建两个哨兵节点，一个用于连接所有小于x的节点，另一个用于连接所有大于等于x的节点。这样可以避免处理头节点可能变化的边界情况。
 * 分割链表：遍历原链表，根据节点值与x的比较结果，将节点分配到两个哨兵节点所代表的两个新链表中。
 * 合并链表：当原链表遍历完成后，将小于x的链表的最后一个节点连接到大于等于x的链表的首个节点。
 * 时间和空间复杂度：最优解应该是时间复杂度O(n)，空间复杂度O(1)。只需要遍历一次链表，同时只使用有限的额外空间。
 * 
 */
class Solution {
public:
	ListNode* partition(ListNode* head, int x) {
		// 创建两个哨兵节点
		ListNode lessHead(0), greaterHead(0);
		ListNode* lessPtr = &lessHead, * greaterPtr = &greaterHead;

		while (head) {
			if (head->val < x) {
				// 将节点添加到小于x的链表
				lessPtr->next = head;
				lessPtr = lessPtr->next;
			}
			else {
				// 将节点添加到大于等于x的链表
				greaterPtr->next = head;
				greaterPtr = greaterPtr->next;
			}
			head = head->next;
		}

		// 合并两个链表
		lessPtr->next = greaterHead.next;
		greaterPtr->next = nullptr; // 需要设置大于等于x的链表的最后一个节点的next为nullptr

		return lessHead.next;
	}
};