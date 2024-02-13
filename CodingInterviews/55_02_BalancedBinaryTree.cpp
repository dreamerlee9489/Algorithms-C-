#include <cstdio>
#include "BinaryTree.h"

// ====================方法1====================
int TreeDepth(const BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return 0;

	int nLeft = TreeDepth(pRoot->m_pLeft);
	int nRight = TreeDepth(pRoot->m_pRight);

	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}

bool IsBalanced_Solution1(const BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return true;

	int left = TreeDepth(pRoot->m_pLeft);
	int right = TreeDepth(pRoot->m_pRight);
	int diff = left - right;
	if (diff > 1 || diff < -1)
		return false;

	return IsBalanced_Solution1(pRoot->m_pLeft)
		&& IsBalanced_Solution1(pRoot->m_pRight);
}

// ====================方法2====================
bool IsBalanced(const BinaryTreeNode* pRoot, int* pDepth)
{
	if (pRoot == nullptr)
	{
		*pDepth = 0;
		return true;
	}

	int left, right;
	if (IsBalanced(pRoot->m_pLeft, &left)
		&& IsBalanced(pRoot->m_pRight, &right))
	{
		int diff = left - right;
		if (diff <= 1 && diff >= -1)
		{
			*pDepth = 1 + (left > right ? left : right);
			return true;
		}
	}

	return false;
}

bool IsBalanced_Solution2(const BinaryTreeNode* pRoot)
{
	int depth = 0;
	return IsBalanced(pRoot, &depth);
}