/**
 * @file palindrome-linked-list.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 234. 回文链表
 * @version 0.1
 * @date 2022-08-08
 * @link https://leetcode.cn/problems/palindrome-linked-list/
 * @copyright Copyright (c) 2022
 *
 */
#include "./ListNode.hpp"
#include <vector>

using namespace std;

class Solution {
public:
	bool isPalindrome(ListNode* head) {
		vector<int> vec;
		while (head != nullptr) {
			vec.emplace_back(head->val);
			head = head->next;
		}
		int left = 0, right = vec.size() - 1;
		while (left < right) {
			if (vec[left] != vec[right])
				return false;
			++left;
			--right;
		}
		return true;
	}
};