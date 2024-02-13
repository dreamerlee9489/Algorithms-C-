#include <cstdio>
#include "Array.h"
#include <set>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

// ====================方法1====================
void GetLeastNumbers_Solution1(int* input, int n, int* output, int k)
{
	if (input == nullptr || output == nullptr || k > n || n <= 0 || k <= 0)
		return;

	int start = 0;
	int end = n - 1;
	int index = Partition(input, n, start, end);
	while (index != k - 1)
	{
		if (index > k - 1)
		{
			end = index - 1;
			index = Partition(input, n, start, end);
		}
		else
		{
			start = index + 1;
			index = Partition(input, n, start, end);
		}
	}

	for (int i = 0; i < k; ++i)
		output[i] = input[i];
}

// ====================方法2====================
typedef multiset<int, std::greater<int> >            intSet;
typedef multiset<int, std::greater<int> >::iterator  setIterator;

void GetLeastNumbers_Solution2(const vector<int>& data, intSet& leastNumbers, int k)
{
	leastNumbers.clear();

	if (k < 1 || data.size() < k)
		return;

	vector<int>::const_iterator iter = data.begin();
	for (; iter != data.end(); ++iter)
	{
		if ((leastNumbers.size()) < k)
			leastNumbers.insert(*iter);

		else
		{
			setIterator iterGreatest = leastNumbers.begin();

			if (*iter < *(leastNumbers.begin()))
			{
				leastNumbers.erase(iterGreatest);
				leastNumbers.insert(*iter);
			}
		}
	}
}