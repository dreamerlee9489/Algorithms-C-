#include <cstdio>
#include "StringUtil.h"
#include <string.h>

char* LeftRotateString(char* pStr, int n)
{
	if (pStr != nullptr)
	{
		int nLength = static_cast<int>(strlen(pStr));
		if (nLength > 0 && n > 0 && n < nLength)
		{
			char* pFirstStart = pStr;
			char* pFirstEnd = pStr + n - 1;
			char* pSecondStart = pStr + n;
			char* pSecondEnd = pStr + nLength - 1;

			// 翻转字符串的前面n个字符
			Reverse(pFirstStart, pFirstEnd);
			// 翻转字符串的后面部分
			Reverse(pSecondStart, pSecondEnd);
			// 翻转整个字符串
			Reverse(pFirstStart, pSecondEnd);
		}
	}

	return pStr;
}