/**
 * @file remove-linked-list-elements.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 203. 移除链表元素
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/remove-linked-list-elements/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

 /**
  * 解题技巧总结：
  * 在这道题目中，我们需要移除链表中所有值等于给定值val的节点。以下是解决这个问题的关键步骤和技巧：
  * 使用哨兵节点（Dummy Node）：为了简化边界条件，特别是当头节点也可能被删除时，可以创建一个哨兵节点（也称为虚拟头节点或Dummy Node），并将其next指针指向链表的真正头节点。这样，即使头节点被删除，我们也可以通过哨兵节点来返回新的头节点。
  * 遍历链表：使用一个指针遍历链表，同时检查每个节点的值是否等于val。
  * 删除目标节点：当发现当前节点的值等于val时，将其前一个节点的next指针指向当前节点的下一个节点，这样就可以将当前节点从链表中移除。
  * 更新指针：每次移除节点后，更新指针以继续遍历链表，直到遍历结束。
  * 返回新头节点：遍历结束后，哨兵节点的next指针指向的就是新的头节点，返回这个新头节点即可。
  * 时间和空间复杂度：时间复杂度为O(n)，其中n是链表的长度，因为需要遍历整个链表。空间复杂度为O(1)，因为我们只需要常数级的额外空间。
  * 注意内存管理：在C++中，如果是使用new分配了节点空间，删除节点时需要确保使用delete来释放内存，避免内存泄漏。
  *
  */
class Solution {
public:
	ListNode* removeElements(ListNode* head, int val) {
		// 创建哨兵节点
		ListNode* sentinel = new ListNode(0);
		sentinel->next = head;

		ListNode* prev = sentinel;
		ListNode* curr = head;

		// 遍历链表
		while (curr != nullptr) {
			if (curr->val == val) {
				// 删除当前节点
				prev->next = curr->next;
				// 如果使用new分配了节点空间，此处应该释放curr指向的节点空间
				// delete curr;
				curr = prev->next; // 更新curr指针
			}
			else {
				prev = curr;
				curr = curr->next;
			}
		}

		ListNode* newHead = sentinel->next;
		delete sentinel; // 释放哨兵节点的空间
		return newHead;
	}
};