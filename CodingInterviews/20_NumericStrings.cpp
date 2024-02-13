#include <stdio.h>

bool scanUnsignedInteger(const char** str)
{
	const char* before = *str;
	while (**str != '\0' && **str >= '0' && **str <= '9')
		++(*str);

	// 当str中存在若干0-9的数字时，返回true
	return *str > before;
}

// 整数的格式可以用[+|-]B表示, 其中B为无符号整数
bool scanInteger(const char** str)
{
	if (**str == '+' || **str == '-')
		++(*str);
	return scanUnsignedInteger(str);
}

// 数字的格式可以用A[.[B]][e|EC]或者.B[e|EC]表示，其中A和C都是
// 整数（可以有正负号，也可以没有），而B是一个无符号整数
bool isNumeric(const char* str)
{
	if (str == nullptr)
		return false;

	bool numeric = scanInteger(&str);

	// 如果出现'.'，接下来是数字的小数部分
	if (*str == '.')
	{
		++str;
		numeric = scanUnsignedInteger(&str) || numeric;
	}

	// 如果出现'e'或者'E'，接下来跟着的是数字的指数部分
	if (*str == 'e' || *str == 'E')
	{
		++str;
		numeric = numeric && scanInteger(&str);
	}

	return numeric && *str == '\0';
}