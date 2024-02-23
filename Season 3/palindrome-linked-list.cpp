/**
 * @file palindrome-linked-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 234. 回文链表
 * @version 0.1
 * @date 2022-07-18
 * @link https://leetcode.cn/problems/palindrome-linked-list/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"

 /**
  * 解题技巧总结：
  * 判断一个链表是否为回文链表需要考虑以下几点：
  * 链表遍历：由于链表是一种线性结构，只能从头到尾进行遍历，不能像数组一样通过索引随机访问。
  * 快慢指针：使用快慢两个指针来找到链表的中点。慢指针每次移动一个节点，快指针每次移动两个节点。当快指针到达链表尾部时，慢指针会位于链表的中间位置。
  * 链表反转：在到达链表中点的同时，反转前半部分的链表。这样在遍历完成后，可以比较前半部分和后半部分是否相同。
  * 回文判断：从链表的中点将链表分为前后两部分，若链表长度为奇数，可以忽略中间的节点。然后比较前半部分和后半部分的每个节点，如果所有节点都相同，则为回文链表。
  * 时间和空间复杂度：最优解应该是时间复杂度O(n)，空间复杂度O(1)。也就是说，在遍历链表的同时完成反转和回文检查，并且不使用额外的存储空间。
  *
  */
class Solution {
public:
	bool isPalindrome(ListNode* head) {
		if (head == nullptr || head->next == nullptr) {
			return true;
		}

		ListNode* slow = head;
		ListNode* fast = head;
		ListNode* prev = nullptr;
		ListNode* temp = nullptr;

		// 使用快慢指针寻找中点，同时反转前半部分链表
		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;

			// 反转前半部分链表
			temp = slow->next;
			slow->next = prev;
			prev = slow;
			slow = temp;
		}

		// 如果链表长度是奇数，忽略中间的元素
		if (fast != nullptr) {
			slow = slow->next;
		}

		// 比较前半部分和后半部分链表
		while (prev != nullptr && slow != nullptr) {
			if (prev->val != slow->val) {
				return false;
			}
			prev = prev->next;
			slow = slow->next;
		}

		return true;
	}
};