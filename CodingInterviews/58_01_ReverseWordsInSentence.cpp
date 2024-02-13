#include <cstdio>
#include "StringUtil.h"
#include <string>

char* ReverseSentence(char* pData)
{
	if (pData == nullptr)
		return nullptr;

	char* pBegin = pData;

	char* pEnd = pData;
	while (*pEnd != '\0')
		pEnd++;
	pEnd--;

	// 翻转整个句子
	Reverse(pBegin, pEnd);

	// 翻转句子中的每个单词
	pBegin = pEnd = pData;
	while (*pBegin != '\0')
	{
		if (*pBegin == ' ')
		{
			pBegin++;
			pEnd++;
		}
		else if (*pEnd == ' ' || *pEnd == '\0')
		{
			Reverse(pBegin, --pEnd);
			pBegin = ++pEnd;
		}
		else
			pEnd++;
	}

	return pData;
}