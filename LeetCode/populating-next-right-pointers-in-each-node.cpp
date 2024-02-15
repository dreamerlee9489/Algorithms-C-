/**
 * @file populating-next-right-pointers-in-each-node.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 116. 填充每个节点的下一个右侧节点指针
 * @version 0.1
 * @date 2022-08-12
 * @link
 * https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <cstdio>
#include <list>

using namespace std;

class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(NULL), right(NULL), next(NULL) {}

	Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
	Node* connect(Node* root) {
		if (root == nullptr) return nullptr;
		Node* start = root;
		while (start->left) {
			Node* current = start;
			while (current) {
				current->left->next = current->right;
				if (current->next)
					current->right->next = current->next->left;
				current = current->next;
			}
			start = start->left;
		}
		return root;
	}
};