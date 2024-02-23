/**
 * @file intersection-of-two-linked-lists.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 160. 相交链表
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/intersection-of-two-linked-lists/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

 /**
  * 为了解决相交链表问题，可以使用两个指针分别遍历两个链表。当一个指针到达链表末尾时，将其重定向到另一个链表的头部继续遍历。如果链表相交，那么这两个指针最终会在相交点相遇。如果链表不相交，那么这两个指针会同时到达各自链表的末尾（即都指向nullptr）。
  * 解题技巧总结：
  * 使用两个指针pA和pB，分别初始化为headA和headB。
  * 同时遍历两个链表，如果指针到达链表末尾，则将其重定向到另一个链表的头部继续遍历。
  * 如果在某一时刻pA和pB相遇，则返回相遇的节点（即相交的起始节点）。
  * 如果两个链表不相交，则最终pA和pB都会指向nullptr，在这种情况下返回nullptr。
  * 这种方法不会破坏链表的原始结构，因为它只涉及遍历操作。
  *
  */
class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		if (headA == nullptr || headB == nullptr) return nullptr;

		ListNode* pA = headA, * pB = headB;
		while (pA != pB) {
			// 如果指针到达链表末尾，则重定向到另一个链表的头部继续遍历
			pA = pA == nullptr ? headB : pA->next;
			pB = pB == nullptr ? headA : pB->next;
		}
		// 如果两个链表相交，pA 和 pB 会在交点相遇；如果不相交，最终都会指向 nullptr
		return pA;
	}
};