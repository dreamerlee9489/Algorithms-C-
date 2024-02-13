/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// 《剑指Offer——名企面试官精讲典型编程题》代码
// 作者：何海涛
//==================================================================

// 面试题66：构建乘积数组
// 题目：给定一个数组A[0, 1, …, n-1]，请构建一个数组B[0, 1, …, n-1]，其
// 中B中的元素B[i] =A[0]×A[1]×… ×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

void BuildProductionArray(const vector<double>& input, vector<double>& output)
{
	int length1 = input.size();
	int length2 = output.size();

	if (length1 == length2 && length2 > 1)
	{
		output[0] = 1;
		for (int i = 1; i < length1; ++i)
		{
			output[i] = output[i - 1] * input[i - 1];
		}

		double temp = 1;
		for (int i = length1 - 2; i >= 0; --i)
		{
			temp *= input[i + 1];
			output[i] *= temp;
		}
	}
}

static bool EqualArrays(const vector<double>& input, const vector<double>& output)
{
	int length1 = input.size();
	int length2 = output.size();

	if (length1 != length2)
		return false;

	for (int i = 0; i < length1; ++i)
	{
		if (abs(input[i] - output[i]) > 0.0000001)
			return false;
	}

	return true;
}
