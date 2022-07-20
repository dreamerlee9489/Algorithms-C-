/**
 * @file subtree-of-another-tree.cpp
 * @author dreamerlee9489@outlook.com
 * @brief 572. 另一棵树的子树
 * @version 0.1
 * @date 2022-07-20
 * @remark https://leetcode.cn/problems/subtree-of-another-tree/
 * @copyright Copyright (c) 2022
 *
 */
#include <string>
#include <iostream>
#include "./TreeNode.hpp"
using namespace std;

class Solution
{
    string postSerialize(TreeNode *root, string &str)
    {
        if (root == nullptr)
            return str.append("#!");
        else
        {
            postSerialize(root->left, str);
            postSerialize(root->right, str);
            return str.append(to_string(root->val) + "!");
        }
    }

public:
    bool isSubtree(TreeNode *root, TreeNode *subRoot)
    {
        if(root == nullptr || subRoot == nullptr)
            return false;
        string str1 = "", str2 = "";
        return postSerialize(root, str1).find(postSerialize(subRoot, str2)) != string::npos;
    }
};

int main(int argc, char const *argv[])
{
    TreeNode *root = new TreeNode(3);
    root->left = new TreeNode(4);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(2);
    TreeNode *subroot = new TreeNode(4);
    subroot->left = new TreeNode(1);
    subroot->right = new TreeNode(2);
    cout << Solution().isSubtree(root, subroot);
    return 0;
}
