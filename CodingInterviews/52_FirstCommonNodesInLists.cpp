#include <cstdio>
#include "List.h"

unsigned int GetListLength(ListNode* pHead)
{
	unsigned int nLength = 0;
	ListNode* pNode = pHead;
	while (pNode != nullptr)
	{
		++nLength;
		pNode = pNode->m_pNext;
	}

	return nLength;
}

ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2)
{
	// 得到两个链表的长度
	unsigned int nLength1 = GetListLength(pHead1);
	unsigned int nLength2 = GetListLength(pHead2);
	int nLengthDif = nLength1 - nLength2;

	ListNode* pListHeadLong = pHead1;
	ListNode* pListHeadShort = pHead2;
	if (nLength2 > nLength1)
	{
		pListHeadLong = pHead2;
		pListHeadShort = pHead1;
		nLengthDif = nLength2 - nLength1;
	}

	// 先在长链表上走几步，再同时在两个链表上遍历
	for (int i = 0; i < nLengthDif; ++i)
		pListHeadLong = pListHeadLong->m_pNext;

	while ((pListHeadLong != nullptr) &&
		(pListHeadShort != nullptr) &&
		(pListHeadLong != pListHeadShort))
	{
		pListHeadLong = pListHeadLong->m_pNext;
		pListHeadShort = pListHeadShort->m_pNext;
	}

	// 得到第一个公共结点
	ListNode* pFisrtCommonNode = pListHeadLong;

	return pFisrtCommonNode;
}