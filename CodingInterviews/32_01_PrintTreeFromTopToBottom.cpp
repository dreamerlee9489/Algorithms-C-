#include <cstdio>
#include "BinaryTree.h"
#include <deque>

void PrintFromTopToBottom(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return;

	std::deque<BinaryTreeNode*> dequeTreeNode;

	dequeTreeNode.push_back(pRoot);

	while (dequeTreeNode.size())
	{
		BinaryTreeNode* pNode = dequeTreeNode.front();
		dequeTreeNode.pop_front();

		printf("%d ", pNode->m_nValue);

		if (pNode->m_pLeft)
			dequeTreeNode.push_back(pNode->m_pLeft);

		if (pNode->m_pRight)
			dequeTreeNode.push_back(pNode->m_pRight);
	}
}