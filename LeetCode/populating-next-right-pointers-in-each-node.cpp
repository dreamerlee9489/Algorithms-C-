/**
 * @file populating-next-right-pointers-in-each-node.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 116. 填充每个节点的下一个右侧节点指针
 * @version 0.1
 * @date 2022-08-12
 * @link https://leetcode.cn/problems/populating-next-right-pointers-in-each-node/ @endlink
 * @copyright Copyright (c) 2022
 *
 */
#include <cstdio>
#include <list>

using namespace std;

class Node {
public:
    int val;
    Node *left;
    Node *right;
    Node *next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node *pLeft, Node *pRight, Node *pNext)
            : val(_val), left(pLeft), right(pRight), next(pNext) {}
};

class Solution {
public:
    Node *connect(Node *root) {
        if (root == nullptr)
            return nullptr;
        list<Node *> _list;
        _list.push_back(root);
        int lv_cnt = 1;
        while (!_list.empty()) {
            Node *node = _list.front();
            _list.pop_front();
            --lv_cnt;
            if (node->left != NULL)
                _list.push_back(node->left);
            if (node->right != NULL)
                _list.push_back(node->right);
            if (lv_cnt == 0) {
                lv_cnt = _list.size();
                auto iter = _list.begin();
                while (iter != _list.end()) {
                    (*iter)->next = next(iter) == _list.end() ? NULL : *next(iter);
                    ++iter;
                }
            }
        }
        return root;
    }
};