#include <cstdio>

struct BinaryTreeNode
{
	double                 m_dbValue;
	BinaryTreeNode* m_pLeft;
	BinaryTreeNode* m_pRight;
};

bool DoesTree1HaveTree2(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	if (pRoot2 == nullptr)
		return true;

	if (pRoot1 == nullptr)
		return false;

	if (!Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
		return false;

	return DoesTree1HaveTree2(pRoot1->m_pLeft, pRoot2->m_pLeft) &&
		DoesTree1HaveTree2(pRoot1->m_pRight, pRoot2->m_pRight);
}

bool Equal(double num1, double num2)
{
	if ((num1 - num2 > -0.0000001) && (num1 - num2 < 0.0000001))
		return true;
	else
		return false;
}

bool HasSubtree(BinaryTreeNode* pRoot1, BinaryTreeNode* pRoot2)
{
	bool result = false;

	if (pRoot1 != nullptr && pRoot2 != nullptr)
	{
		if (Equal(pRoot1->m_dbValue, pRoot2->m_dbValue))
			result = DoesTree1HaveTree2(pRoot1, pRoot2);
		if (!result)
			result = HasSubtree(pRoot1->m_pLeft, pRoot2);
		if (!result)
			result = HasSubtree(pRoot1->m_pRight, pRoot2);
	}

	return result;
}

// ====================辅助测试代码====================
BinaryTreeNode* CreateBinaryTreeNode(double dbValue)
{
	BinaryTreeNode* pNode = new BinaryTreeNode();
	pNode->m_dbValue = dbValue;
	pNode->m_pLeft = nullptr;
	pNode->m_pRight = nullptr;

	return pNode;
}

void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight)
{
	if (pParent != nullptr)
	{
		pParent->m_pLeft = pLeft;
		pParent->m_pRight = pRight;
	}
}

void DestroyTree(BinaryTreeNode* pRoot)
{
	if (pRoot != nullptr)
	{
		BinaryTreeNode* pLeft = pRoot->m_pLeft;
		BinaryTreeNode* pRight = pRoot->m_pRight;

		delete pRoot;
		pRoot = nullptr;

		DestroyTree(pLeft);
		DestroyTree(pRight);
	}
}