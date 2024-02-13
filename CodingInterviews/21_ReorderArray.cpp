#include <cstdio>

void Reorder(int* pData, unsigned int length, bool (*func)(int))
{
	if (pData == nullptr || length == 0)
		return;

	int* pBegin = pData;
	int* pEnd = pData + length - 1;

	while (pBegin < pEnd)
	{
		// 向后移动pBegin
		while (pBegin < pEnd && !func(*pBegin))
			pBegin++;

		// 向前移动pEnd
		while (pBegin < pEnd && func(*pEnd))
			pEnd--;

		if (pBegin < pEnd)
		{
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

bool isEven(int n)
{
	return (n & 1) == 0;
}

// ====================方法一====================
void ReorderOddEven_1(int* pData, unsigned int length)
{
	if (pData == nullptr || length == 0)
		return;

	int* pBegin = pData;
	int* pEnd = pData + length - 1;

	while (pBegin < pEnd)
	{
		// 向后移动pBegin，直到它指向偶数
		while (pBegin < pEnd && (*pBegin & 0x1) != 0)
			pBegin++;

		// 向前移动pEnd，直到它指向奇数
		while (pBegin < pEnd && (*pEnd & 0x1) == 0)
			pEnd--;

		if (pBegin < pEnd)
		{
			int temp = *pBegin;
			*pBegin = *pEnd;
			*pEnd = temp;
		}
	}
}

// ====================方法二====================
void ReorderOddEven_2(int* pData, unsigned int length)
{
	Reorder(pData, length, isEven);
}