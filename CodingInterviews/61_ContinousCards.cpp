#include <cstdio>
#include <cstdlib>

int Compare(const void* arg1, const void* arg2)
{
	return *(int*)arg1 - *(int*)arg2;
}

bool IsContinuous(int* numbers, int length)
{
	if (numbers == nullptr || length < 1)
		return false;

	qsort(numbers, length, sizeof(int), Compare);

	int numberOfZero = 0;
	int numberOfGap = 0;

	// 统计数组中0的个数
	for (int i = 0; i < length && numbers[i] == 0; ++i)
		++numberOfZero;

	// 统计数组中的间隔数目
	int small = numberOfZero;
	int big = small + 1;
	while (big < length)
	{
		// 两个数相等，有对子，不可能是顺子
		if (numbers[small] == numbers[big])
			return false;

		numberOfGap += numbers[big] - numbers[small] - 1;
		small = big;
		++big;
	}

	return (numberOfGap > numberOfZero) ? false : true;
}