/**
 * @file populating-next-right-pointers-in-each-node-ii.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 117. 填充每个节点的下一个右侧节点指针 II
 * @version 0.1
 * @date 2024-02-15
 * @link https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/description/
 * @copyright Copyright (c) 2024
 *
 */
#include <cstdio>
#include <list>
#include <iostream>
using namespace std;

// 定义二叉树节点结构体
struct Node {
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

	Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
	Node* connect(Node* root) {
		if (root == nullptr) return nullptr;
		Node* mostleft = root, * curr = nullptr, * prev = nullptr;
		while (mostleft) {
			curr = mostleft;
			prev = nullptr;
			mostleft = nullptr;
			while (curr) {
				for (Node* child : { curr->left, curr->right }) {
					if (child) {
						if (prev) prev->next = child;
						else mostleft = child;
						prev = child;
					}
				}
				curr = curr->next;
			}
		}
		return root;
	}
};