#include <cstdio>
#include "BinaryTree.h"
#include <queue>

void Print(BinaryTreeNode* pRoot)
{
	if (pRoot == nullptr)
		return;

	std::queue<BinaryTreeNode*> nodes;
	nodes.push(pRoot);
	int nextLevel = 0;
	int toBePrinted = 1;
	while (!nodes.empty())
	{
		BinaryTreeNode* pNode = nodes.front();
		printf("%d ", pNode->m_nValue);

		if (pNode->m_pLeft != nullptr)
		{
			nodes.push(pNode->m_pLeft);
			++nextLevel;
		}
		if (pNode->m_pRight != nullptr)
		{
			nodes.push(pNode->m_pRight);
			++nextLevel;
		}

		nodes.pop();
		--toBePrinted;
		if (toBePrinted == 0)
		{
			printf("\n");
			toBePrinted = nextLevel;
			nextLevel = 0;
		}
	}
}