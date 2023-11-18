/**
 * @file copy-list-with-random-pointer.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 138. 复制带随机指针的链表
 * @version 0.1
 * @date 2022-08-07
 * @link https://leetcode.cn/problems/copy-list-with-random-pointer/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>

class Node {
public:
	int val;
	Node* next;
	Node* random;

	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};

class Solution {
public:
	Node* copyRandomList(Node* head) {
		Node* p = head, * newHead = new Node(0), * newTail = newHead;
		while (p != NULL) {
			Node* newNode = new Node(p->val);
			newTail->next = newNode;
			newTail = newTail->next;
			p = p->next;
		}
		p = head;
		Node* q = newHead->next;
		while (p != NULL) {
			Node* tmp0 = head, * tmp1 = newHead->next;
			int index = 0;
			while (tmp0 != NULL) {
				if (p->random == NULL) {
					tmp0 = NULL;
					tmp1 = NULL;
					break;
				}
				if (tmp0 == p->random)
					break;
				tmp0 = tmp0->next;
				++index;
			}
			while (index > 0) {
				tmp1 = tmp1->next;
				--index;
			}
			q->random = tmp1;
			p = p->next;
			q = q->next;
		}
		return newHead->next;
	}
};

int main(int argc, char const* argv[]) {
	Node* head = new Node(7);
	head->next = new Node(13);
	head->next->next = new Node(11);
	head->next->next->next = new Node(10);
	head->next->next->next->next = new Node(1);
	head->random = NULL;
	head->next->random = head;
	head->next->next->random = head->next->next->next->next;
	head->next->next->next->random = head->next->next;
	head->next->next->next->next->random = head;
	Node* res = Solution().copyRandomList(head);
	return 0;
}
